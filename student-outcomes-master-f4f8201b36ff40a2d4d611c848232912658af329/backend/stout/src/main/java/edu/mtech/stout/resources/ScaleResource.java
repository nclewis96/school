package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Scale;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.ScaleDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/scales/{scaleId}")
@Produces(MediaType.APPLICATION_JSON)
public class ScaleResource {

  private ScaleDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public ScaleResource(ScaleDAO dao) {
    this.dao = dao;
  }

  @GET
  @UnitOfWork
  public Scale getScale(@Auth User user, @PathParam("scaleId") LongParam scaleId) {
    if(queryBySelector.queryByProgramId(user,findSafely(scaleId.get()).getProgId()))
      return findSafely(scaleId.get());
    throw new NotAuthorizedException("Cannot get a scale not in a program you do not have access to");
  }

  private Scale findSafely(long scaleId) {
    return dao.findById(scaleId).orElseThrow(() -> new NotFoundException("No such scale."));
  }

  @PATCH
  @UnitOfWork
  public Scale updateScale(@Auth User user, @PathParam("scaleId") LongParam scaleId, Scale scale)
  {
    if(queryBySelector.queryByProgramId(user, scale.getProgId()))
      return dao.update(scale);
    throw new NotAuthorizedException("Cannot update a scale not in a program you do not have access to");
  }

  @DELETE
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Status deleteScale(@Auth User user, @PathParam("scaleId") LongParam scaleId) {
    if(queryBySelector.queryByProgramId(user,findSafely(scaleId.get()).getProgId())) {
      Status status = new Status();
      status.setId(scaleId.get().intValue());
      status.setAction("DELETE");
      status.setResource("Scale");

      boolean success = dao.delete(findSafely(scaleId.get().intValue()));

      if (success) {
        status.setMessage("Successfully deleted scale");
        status.setStatus(200);
      } else {
        status.setMessage("Error deleting scale");
        status.setStatus(500);
      }

      return status;
    }else{
      throw new NotAuthorizedException("Cannot delete a scale not in a program you do not have access to");
    }
  }
}