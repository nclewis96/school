package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Offering;
import edu.mtech.stout.core.OfferingStudent;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.OfferingStudentDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/offering-students/{studentId}")
@Produces(MediaType.APPLICATION_JSON)
public class OfferingStudentResource {
  private OfferingStudentDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramDAO programDao;

  public OfferingStudentResource(OfferingStudentDAO dao, ProgramDAO programDao){
    this.dao = dao;
    this.programDao = programDao;
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OfferingStudent getOfferingStudent(@Auth User user, @PathParam("studentId") LongParam studentId) {
    List<Program> p = programDao.findByStudentId(studentId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(studentId.get());
      }else{
        throw new NotAuthorizedException("Cannot get a Student not in your program");
      }
    }else{
      throw new NotFoundException("No students are available with that Id");
    }
  }

  private OfferingStudent findSafely(long studentId){
    return dao.findById(studentId).orElseThrow(() -> new NotFoundException("No such Student."));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OfferingStudent updateOfferingStudent(@Auth User user,@PathParam("studentId")LongParam studentId, OfferingStudent offeringStudent){
    List<Program> p = programDao.findByOffering(studentId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return  dao.update(offeringStudent);
      }else{
        throw new NotAuthorizedException("Cannot update a Student not in your program");
      }
    }else{
      throw new NotFoundException("No students are available with that Id");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Status deleteOfferingStudent(@Auth User user, @PathParam("studentId") LongParam studentId){
    List<Program> p = programDao.findByStudentId(studentId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(studentId.get().intValue());
        status.setAction("DELETE");
        status.setResource("OfferingStudent");

        boolean success = dao.delete(findSafely(studentId.get().intValue()));

        if(success){
          status.setMessage("Successfully deleted student");
          status.setStatus(200);
        }else{
          status.setMessage("Error deleting student");
          status.setStatus(500);
        }
        return status;

      }else{
        throw new NotAuthorizedException("Cannot delete a Student not in your program");
      }
    }else{
      throw new NotFoundException("No students are available with that Id");
    }

  }


}
