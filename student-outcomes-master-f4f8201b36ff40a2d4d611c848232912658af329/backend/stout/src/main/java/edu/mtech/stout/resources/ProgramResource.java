package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/programs/{programId}")
@Produces(MediaType.APPLICATION_JSON)
public class ProgramResource {

  private ProgramDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public ProgramResource(ProgramDAO dao) {
    this.dao = dao;
  }

  @GET
  @RolesAllowed({"Amdin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public Program getProgram(@Auth User user, @PathParam("programId") LongParam programId) {
    if(queryBySelector.getUserPerm(user) == 1 || queryBySelector.queryByProgramId(user,programId.get()))
      return findSafely(programId.get());
    throw new NotAuthorizedException("Cannot get a program you're not associated with.");
  }

  private Program findSafely(long programId) {
    return dao.findById(programId).orElseThrow(() -> new NotFoundException("No such program."));
  }

  @PATCH
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Program updateProgram(@PathParam("programId") LongParam programId, Program program) {
    return dao.update(program);
  }

  @DELETE
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Status deleteProgram(@PathParam("programId") LongParam programId) {
    Status status = new Status();
    status.setId(programId.get().intValue());
    status.setAction("DELETE");
    status.setResource("Program");

    boolean success = dao.delete(findSafely(programId.get().intValue()));

    if (success) {
      status.setMessage("Successfully deleted program");
      status.setStatus(200);
    } else {
      status.setMessage("Error deleting program");
      status.setStatus(500);
    }

    return status;
  }
}
