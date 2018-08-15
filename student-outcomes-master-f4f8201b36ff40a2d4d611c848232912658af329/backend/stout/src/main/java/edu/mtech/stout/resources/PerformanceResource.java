package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Performance;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.PerformanceDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import java.util.List;


@Path("/performance-indicators/{performanceId}")
@Produces
public class PerformanceResource {

  private PerformanceDAO dao;
  private ProgramDAO programDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public PerformanceResource(PerformanceDAO dao, ProgramDAO programDao){

    this.dao = dao;
    this.programDao = programDao;
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public Performance getPerformance(@Auth User user, @PathParam("performanceId")LongParam performanceId){
    List<Program> p = programDao.findByPerformance(performanceId.get());
    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i = 0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId() )){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(performanceId.get());
      }else{
        throw new NotAuthorizedException("Cannot get a performance indicator not in your program");
      }
    }else{
      throw new NotFoundException("The requested performance indicator does not exist");
    }

  }

  private Performance findSafely(long performanceId){
    return  dao.findById(performanceId).orElseThrow(() -> new NotFoundException("No such Performance Indicator"));
  }

  @PATCH
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public Performance updatePeformance(@Auth User user, @PathParam("performanceId") LongParam performanceId, Performance performance){
    List<Program> p = programDao.findByPerformance(performanceId.get());
    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i = 0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId() )){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(performance);
      }else{
        throw new NotAuthorizedException("Cannot get a performance indicator not in your program");
      }
    }else{
      throw new NotFoundException("The requested performance indicator does not exist");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Status deletePerformance(@Auth User user, @PathParam("performanceId") LongParam performanceId) {
    List<Program> p = programDao.findByPerformance(performanceId.get());
    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i = 0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId() )){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(performanceId.get().intValue());
        status.setAction("DELETE");
        status.setResource("Performance");

        boolean success = dao.delete(findSafely(performanceId.get().intValue()));

        if (success) {
          status.setMessage("Successfully deleted Performance Indicator");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting Performance Indicator");
          status.setStatus(500);
        }

        return status;
      }else{
        throw new NotAuthorizedException("Cannot get a performance indicator not in your program");
      }
    }else{
      throw new NotFoundException("The requested performance indicator does not exist");
    }
  }
}
