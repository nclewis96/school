package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Offering;
import edu.mtech.stout.core.Permissions;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.OfferingDAO;
import edu.mtech.stout.db.PermissionsDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.auth.UnauthorizedHandler;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/offerings")
@Produces(MediaType.APPLICATION_JSON)
public class OfferingResourceList {


  private OfferingDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramDAO programDao;


  public OfferingResourceList(OfferingDAO dao, ProgramDAO programDao) {
    this.dao = dao;
    this.programDao = programDao;
  }

  @POST
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Offering createOffering(@Auth User user, Offering offering) {
    List<Program> progList = programDao.findByOffering(offering.getId());
    if(progList.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < progList.size(); i++){
        if(queryBySelector.queryByProgramId(user, progList.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.create(offering);
      }else{
        throw new NotAuthorizedException("Cannot create Offering not in your program");
      }
    }else{
      throw new NotFoundException("The offering is not associated with any programs");
    }
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public List<Offering> getOfferingList(@Auth User user, @QueryParam("programId") LongParam programId,
                                        @QueryParam("userId") LongParam userId) {
    long permLevel = queryBySelector.getUserPerm(user);
    //If the User has access to the requested Program allow query
    if (permLevel == 2 && queryBySelector.queryByProgramId(user, programId)) {
      return dao.findByProgramId(programId.get());
    } //If userId is null, default to the current User's userId
    else if (userId == null){
      return dao.findByUser(user.getId());
    }//If User is not a Prog. Coord. and requested a userId throw an exception
    else if(permLevel != 2 && userId != null){
      throw new NotAuthorizedException("You cannot request another Faculty member's courses");
    }//If User is a Prog. Coord. Allow a passed in userId
    else if(permLevel == 2 && userId != null) {
      return dao.findByUser(userId.get());
    } else{
      return dao.findAll();
    }

  }

}
