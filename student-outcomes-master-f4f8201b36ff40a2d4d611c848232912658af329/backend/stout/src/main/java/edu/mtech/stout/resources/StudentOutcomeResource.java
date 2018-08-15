package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.StudentOutcome;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.StudentOutcomeDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.awt.*;
import java.util.List;

@Path("/student-outcomes/{studentId}/{outcomeId}")
@Produces(MediaType.APPLICATION_JSON)
public class StudentOutcomeResource {

  private StudentOutcomeDAO dao;
  private ProgramDAO programDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public StudentOutcomeResource(StudentOutcomeDAO dao, ProgramDAO programDao){
    this.programDao = programDao;
    this.dao = dao;
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public StudentOutcome getStudentOutcome(@Auth User user, @PathParam("studentId")LongParam studentId, @PathParam("outcomeId") LongParam outcomeId){
    List<Program> p = programDao.findByStudentId(studentId.get());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(studentId.get(),outcomeId.get());
      }else{
        throw new NotAuthorizedException("Cannot get a student not in your program");
      }
    }else{
      throw new NotFoundException("No Students are available with that Id");
    }
  }

  private StudentOutcome findSafely(long studentId, long outcomeId){
    return dao.findById(new StudentOutcome(studentId, outcomeId)).orElseThrow(()-> new NotFoundException("No such Student Outcome"));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public StudentOutcome updateStudentOutcome(@Auth User user, @PathParam("studentId")LongParam studentId, @PathParam("outcomeId")LongParam outcomeId, StudentOutcome outcome){
    List<Program> p = programDao.findByStudentId(studentId.get());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(outcome);
      }else{
        throw new NotAuthorizedException("Cannot update a student not in your program");
      }
    }else{
      throw new NotFoundException("No Students are available with that Id");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Status deleteStudentOutcome(@Auth User user, @PathParam("studentId")LongParam studentId, @PathParam("outcomeId")LongParam outcomeId) {
    List<Program> p = programDao.findByStudentId(studentId.get());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(outcomeId.get().longValue());
        status.setAction("DELETE");
        status.setResource("StudentOutcome");

        boolean success = dao.delete(findSafely(studentId.get().longValue(), outcomeId.get().longValue()));

        if (success) {
          status.setMessage("Successfully deleted Student Outcome");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting Student Outcome");
          status.setStatus(500);
        }
        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete a student not in your program");
      }
    }else{
      throw new NotFoundException("No Students are available with that Id");
    }

  }
}
