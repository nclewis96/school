package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Assign;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.AssignDAO;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/assigns/{assignId}")
@Produces(MediaType.APPLICATION_JSON)
public class AssignResource {

  private AssignDAO dao;
  private CourseDAO courseDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public AssignResource(AssignDAO dao, CourseDAO courseDao) {
    this.dao = dao;
    this.courseDao = courseDao;
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Assign getAssign(@Auth User user, @PathParam("assignId") LongParam assignId) {
    //Checks to see if the User has access to the Assign's Program
    List<Course> c = courseDao.findByAssignId(assignId.get());
    if(c.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(assignId.get());
      }else{
        throw new NotAuthorizedException("Cannot get assign not in your program");
      }
    }else{
      throw new NotFoundException("No Assigns are available in your program.");
    }

  }

  private Assign findSafely(long assignId) {

    return dao.findById(assignId).orElseThrow(() -> new NotFoundException("No such Assign."));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Assign updateAssign(@Auth User user, @PathParam("assignId") LongParam assignId, Assign assign) {
    List<Course> c = courseDao.findByAssignId(assignId.get());
    if (c.size() > 0) {
      Boolean hasAccess = false;
      for(int i =0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(assign);
      }else{
        throw new NotAuthorizedException("Cannot update assign not in your program");
      }
    }else{
      throw new NotFoundException("The Assign you are trying to update is not in your program.");
    }

  }

  @DELETE
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Status deleteAssign(@Auth User user, @PathParam("assignId") LongParam assignId) {
    List<Course> c = courseDao.findByAssignId(assignId.get());
    if (c.size() > 0) {
      Boolean hasAccess = false;
      for(int i =0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(assignId.get().intValue());
        status.setAction("DELETE");
        status.setResource("Assign");

        boolean success = dao.delete(findSafely(assignId.get().intValue()));

        if (success) {
          status.setMessage("Successfully deleted assign");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting assign");
          status.setStatus(500);
        }
        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete assign not in your program");
      }
    }else{
      throw new NotFoundException("The Assign you are trying to delete is in your program.");
    }

  }

}