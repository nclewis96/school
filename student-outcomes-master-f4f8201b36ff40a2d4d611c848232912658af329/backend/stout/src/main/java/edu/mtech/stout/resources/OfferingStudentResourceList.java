package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.OfferingStudent;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.OfferingStudentDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
 import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/offering-students")
@Produces(MediaType.APPLICATION_JSON)
public class OfferingStudentResourceList {

  private OfferingStudentDAO dao;
  private ProgramDAO programDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public OfferingStudentResourceList(OfferingStudentDAO dao, ProgramDAO programDao){
    this.dao = dao;
    this.programDao = programDao;
  }

  @POST
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OfferingStudent createOfferingStudent(@Auth User user, OfferingStudent offeringStudent){
    List<Program> p = programDao.findByOffering(offeringStudent.getOfferingId());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.create(offeringStudent);
      }else{
        throw new NotAuthorizedException("Cannot create a Student not in your program");
      }
    }else {
      throw new NotFoundException("No students are available with that Id");
    }

  }

  @GET
  @PermitAll
  @UnitOfWork
  public List<OfferingStudent> getOfferingStudentList(@Auth User user, @QueryParam("programId")LongParam programId){
    if(programId != null){
        if(queryBySelector.queryByProgramId(user, programId)){
          return dao.findAll();
        }else{
          throw new NotAuthorizedException("Cannot access students not in your program");
        }
    }else {
      throw new NotFoundException("No students are available with that Id");
    }

  }

}
