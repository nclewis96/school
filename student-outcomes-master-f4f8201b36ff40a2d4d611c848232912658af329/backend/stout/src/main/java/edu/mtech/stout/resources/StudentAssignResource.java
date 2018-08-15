package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.StudentAssign;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.StudentAssignDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/student-assigns/{studentId}/{assignId}")
@Produces(MediaType.APPLICATION_JSON)
public class StudentAssignResource {
  private StudentAssignDAO dao;
  private ProgramDAO programDao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  public StudentAssignResource(StudentAssignDAO dao, ProgramDAO programDao){
    this.dao = dao;
    this.programDao = programDao;
  }

  @GET
  @PermitAll
  @UnitOfWork
  public StudentAssign getStudentAssign(@Auth User user, @PathParam("studentId")LongParam studentId, @PathParam("assignId")LongParam assignId){
    List<Program> p = programDao.findByStudentAssign(studentId.get(),assignId.get());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(studentId.get(), assignId.get());
      }else{
        throw new NotAuthorizedException("Cannot get a student assignment not in your program");
      }
    }else{
      throw new NotFoundException("No Student assignments are available with that Id");
    }
  }

  private StudentAssign findSafely(long studentId, long assignId){
    return  dao.findById(new StudentAssign(studentId, assignId)).orElseThrow(() -> new NotFoundException("No such Student Assign"));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public StudentAssign updateStudentAssign(@Auth User user, @PathParam("studentId")LongParam studentId, @PathParam("assignId")LongParam assignId, StudentAssign assign){
    List<Program> p = programDao.findByStudentAssign(studentId.get(),assignId.get());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(assign);
      }else{
        throw new NotAuthorizedException("Cannot update a student assignment not in your program");
      }
    }else{
      throw new NotFoundException("No Student assignments are available with that Id");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Status deleteStudentAssign(@Auth User user, @PathParam("studentId")LongParam studentId, @PathParam("assignId")LongParam assignId){
    List<Program> p = programDao.findByStudentAssign(studentId.get(),assignId.get());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(assignId.get().longValue());
        status.setAction("DELETE");
        status.setResource("StudentAssign");

        boolean success = dao.delete(findSafely(studentId.get().longValue(), assignId.get().longValue()));

        if(success){
          status.setMessage("Successfully deleted Student Assign");
          status.setStatus(200);
        }else{
          status.setMessage("Error deleting Student Assign");
          status.setStatus(500);
        }
        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete a student assignment not in your program");
      }
    }else{
      throw new NotFoundException("No students are available with that Id");
    }

  }

}
