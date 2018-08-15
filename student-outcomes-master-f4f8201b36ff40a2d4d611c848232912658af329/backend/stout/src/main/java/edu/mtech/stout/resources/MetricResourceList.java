package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Metric;
import edu.mtech.stout.db.MetricDAO;
import edu.mtech.stout.db.PermissionsDAO;
import io.dropwizard.hibernate.UnitOfWork;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.core.User;
import io.dropwizard.auth.Auth;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;
import java.util.Optional;

@Path("/metrics")
@Produces(MediaType.APPLICATION_JSON)
public class MetricResourceList {

  private MetricDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();


  public MetricResourceList(MetricDAO dao) {
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Metric createMetric(@Auth User user, Metric metric) {
    Optional<Metric> m = dao.findById(metric.getId());
    if(m.isPresent()){
      if(queryBySelector.queryByProgramId(user,m.get().getProgramId())){
        return dao.create(metric);
      }
      throw new NotAuthorizedException("Cannot create Metric not in your program");
    }else{
      throw new NotFoundException("No metrics are available in your program.");
    }
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public List<Metric> getMetricList(@Auth User user, @QueryParam("programId") LongParam programId) {
    if (queryBySelector.queryByProgramId(user, programId)) {
      if (queryBySelector.queryUserPermForProg(user, programId.get(), 2)) {
        return dao.findByProgramId(programId.get());
      } else {
        return dao.findAll();
      }
    }else{
      throw new NotAuthorizedException("Cannot retrieve Metrics not in your Program");
    }
  }

}
