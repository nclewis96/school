package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Metric;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.MetricDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.Optional;

@Path("/metrics/{metricId}")
@Produces(MediaType.APPLICATION_JSON)
public class MetricResource {

  private MetricDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public MetricResource(MetricDAO dao, ProgramDAO pDao) {
    this.dao = dao;
  }

  @GET
  @UnitOfWork
  public Metric getMetric(@Auth User user, @PathParam("metricId") LongParam metricId) {
    Optional<Metric> m = dao.findById(metricId.get());
    if(m.isPresent()){
      if(queryBySelector.queryByProgramId(user,m.get().getProgramId())){
        return findSafely(metricId.get());
      }
      throw new NotAuthorizedException("Cannot get Metric not in your program");
    }else{
      throw new NotFoundException("No metrics are available in your program.");
    }
  }

  private Metric findSafely(long metricId) {
    return dao.findById(metricId).orElseThrow(() -> new NotFoundException("No such metric."));
  }

  @PATCH
  @UnitOfWork
  public Metric updateMetric(@Auth User user, @PathParam("metricId") LongParam metricId, Metric metric) {
    Optional<Metric> m = dao.findById(metricId.get());
    if(m.isPresent()){
      if(queryBySelector.queryByProgramId(user,m.get().getProgramId())){
        return dao.update(metric);
      }
      throw new NotAuthorizedException("Cannot update Metric not in your program");
    }else{
      throw new NotFoundException("No metrics are available in your program.");
    }
  }

  @DELETE
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Status deleteMetric(@Auth User user, @PathParam("metricId") LongParam metricId) {
    Optional<Metric> m = dao.findById(metricId.get());
    if(m.isPresent()){
      if(queryBySelector.queryByProgramId(user,m.get().getProgramId())){
        Status status = new Status();
        status.setId(metricId.get().intValue());
        status.setAction("DELETE");
        status.setResource("Metric");

        boolean success = dao.delete(findSafely(metricId.get().intValue()));

        if (success) {
          status.setMessage("Successfully deleted metric");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting metric");
          status.setStatus(500);
        }
        return status;
      }
      throw new NotAuthorizedException("Cannot delete Metric not in your program");
    }else{
      throw new NotFoundException("No metrics are available in your program.");
    }

  }


}