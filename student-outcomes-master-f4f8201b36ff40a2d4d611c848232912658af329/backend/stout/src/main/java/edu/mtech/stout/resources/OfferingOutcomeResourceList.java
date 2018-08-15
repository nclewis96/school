package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.OfferingOutcome;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.OfferingOutcomeDAO;
import edu.mtech.stout.db.PermissionsDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.*;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;
import java.util.Optional;

@Path("/offering-outcomes")
@Produces(MediaType.APPLICATION_JSON)
public class OfferingOutcomeResourceList {

  private OfferingOutcomeDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramDAO programDao;

  public OfferingOutcomeResourceList(OfferingOutcomeDAO dao, ProgramDAO programDAO){
    this.dao = dao;
    this.programDao = programDAO;
  }

  @POST
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public OfferingOutcome createOfferingOutcome(@Auth User user, OfferingOutcome offeringOutcome) {
    List<Program> progList = programDao.findByOffering(offeringOutcome.getOfferingId());
    if(progList.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < progList.size(); i++){
        if(queryBySelector.queryByProgramId(user, progList.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return  dao.create(offeringOutcome);
      }else{
        throw new NotAuthorizedException("Cannot create Offering Outcome not in your program");
      }
    }else{
      throw new NotFoundException("The offering is not associated with any programs");
    }
  }

  @GET
  @PermitAll
  @UnitOfWork
  public List<OfferingOutcome> getOfferingOutcomeList(@Auth User user, @QueryParam("programId")LongParam programId){
    if (programId != null){
      if(queryBySelector.queryByProgramId(user, programId.get())){
        return dao.findProgramId(programId.get());
      }else{
        return dao.findAll();
      }
    }else{
      throw new NotAuthorizedException("Cannot get Offering Outcomes not in your program");
    }
  }
}
