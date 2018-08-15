package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.OutcomeAssign;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.OutcomeAssignDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/outcome-assigns/{outcomeId}/{assignId}")
@Produces(MediaType.APPLICATION_JSON)
public class OutcomeAssignResource {
  OutcomeAssignDAO dao;
  QueryBySelector queryBySelector = new QueryBySelector();
  CourseDAO courseDao;
  public OutcomeAssignResource(OutcomeAssignDAO dao, CourseDAO courseDao){
    this.dao = dao;
    this.courseDao = courseDao;
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OutcomeAssign getOutcomeAssign(@Auth User user, @PathParam("outcomeId")LongParam outcomeId, @PathParam("assignId")LongParam assignId){
    List<Course> c = courseDao.findByAssignId(assignId.get());
    if(c.size() > 0){
      if(queryBySelector.queryByProgramId(user, c.get(0).getProgramId())){
        return findSafely(assignId.get(), outcomeId.get());
      }else{
        throw new NotAuthorizedException("Cannot get OutcomeAssign not in your program");
      }
    }else{
      throw new NotFoundException("No outcome assignments are available in your program.");
    }
  }

  private OutcomeAssign findSafely(long assignId, long outcomeId){
    return dao.findById(new OutcomeAssign(outcomeId,assignId)).orElseThrow(() -> new NotFoundException("No such Outcome Assign"));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OutcomeAssign updateOutcomeAssign(@Auth User user, @PathParam("outcomeId") LongParam outcomeId,
                                           @PathParam("assignId") LongParam assignId, OutcomeAssign outcomeAssign){
    List<Course> c = courseDao.findByAssignId(assignId.get());
    if (c.size() > 0) {
      Boolean hasAccess = false;
      for(int i = 0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess ){
        return dao.update(outcomeAssign);
      }else{
        throw new NotAuthorizedException("Cannot update outcome assignment not in your program");
      }
    }else{
      throw new NotFoundException("The outcome assignments you are trying to update is not in your program.");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Status deleteOutcomeAssign(@Auth User user, @PathParam("outcomeId")LongParam outcomeId, @PathParam("assignId")LongParam assignId){
    List<Course> c = courseDao.findByAssignId(assignId.get());
    if (c.size() > 0) {
      Boolean hasAccess = false;
      for(int i = 0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess ){
        Status status = new Status();
        status.setId(outcomeId.get().intValue());
        status.setAction("DELETE");
        status.setResource("OutcomeAssign");

        boolean success = dao.delete(findSafely(assignId.get().longValue(),outcomeId.get().longValue()));

        if (success) {
          status.setMessage("Successfully deleted outcome assign");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting outcome assign");
          status.setStatus(500);
        }
        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete outcome assignment not in your program");
      }
    }else{
      throw new NotFoundException("The outcome assignment you are trying to delete is in your program.");
    }
  }
}
