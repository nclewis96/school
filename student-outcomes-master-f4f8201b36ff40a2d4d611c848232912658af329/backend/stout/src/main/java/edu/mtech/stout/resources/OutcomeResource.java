package edu.mtech.stout.resources;


import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.Outcome;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.OutcomeDAO;
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

@Path("/outcomes/{outcomeId}")
@Produces(MediaType.APPLICATION_JSON)
public class OutcomeResource {

  OutcomeDAO dao;
  CourseDAO courseDao;
  QueryBySelector queryBySelector = new QueryBySelector();

  public OutcomeResource(OutcomeDAO dao, CourseDAO courseDao) {
    this.dao = dao;
    this.courseDao = courseDao;
  }

  @GET
  @PermitAll
  @UnitOfWork
  public Outcome getOutcome(@Auth User user, @PathParam("outcomeId") LongParam outcomeId) {
    List<Course> c = courseDao.findByOutcome(outcomeId.get());
    if(c.size()>0){
      Boolean hasAccess = false;
      for(int i = 0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(outcomeId.get());
      }else{
        throw new NotAuthorizedException("Cannot get an outcome not in your program");
      }
    }else{
      throw new NotFoundException("The outcome is not associated with any programs");
    }

  }

  private Outcome findSafely(long outcomeId) {

    return dao.findById(outcomeId).orElseThrow(() -> new NotFoundException("No such outcome."));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Outcome updateOutcome(@Auth User user, @PathParam("outcomeId") LongParam outcomeId, Outcome outcome) {
    List<Course> c = courseDao.findByOutcome(outcomeId.get());
    if(c.size()>0){
      Boolean hasAccess = false;
      for(int i = 0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(outcome);
      }else{
        throw new NotAuthorizedException("Cannot update an outcome not in your program");
      }
    }else{
      throw new NotFoundException("The outcome is not associated with any programs");
    }

  }

  @DELETE
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Status deleteOutcome(@Auth User user, @PathParam("outcomeId") LongParam outcomeId) {
    List<Course> c = courseDao.findByOutcome(outcomeId.get());
    if(c.size()>0){
      Boolean hasAccess = false;
      for(int i = 0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(outcomeId.get().intValue());
        status.setAction("DELETE");
        status.setResource("Outcome");

        boolean success = dao.delete(findSafely(outcomeId.get().intValue()));

        if (success) {
          status.setMessage("Successfully deleted outcome");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting outcome");
          status.setStatus(500);
        }

        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete an outcome not in your program");
      }
    }else{
      throw new NotFoundException("The outcome is not associated with any programs");
    }

  }
}
