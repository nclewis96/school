package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.ProgramCutoff;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramCutoffDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/program-cutoffs/{programId}/{semesterId}")
@Produces(MediaType.APPLICATION_JSON)
public class ProgramCutoffResource {

  private ProgramCutoffDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public ProgramCutoffResource(ProgramCutoffDAO dao, ProgramDAO programDao){
    this.dao = dao;
  }

  @GET
  @PermitAll
  @UnitOfWork
  public ProgramCutoff getProgramCutoff(@Auth User user, @PathParam("programId")LongParam programId, @PathParam("semesterId") LongParam semesterId){
    if(queryBySelector.queryByProgramId(user, programId.get())){
      return findSafely(programId.get(), semesterId.get());
    }
    throw new NotAuthorizedException("Cannot get a Program Cutoff not in your program");
  }

  private ProgramCutoff findSafely(long programId, long semesterId){
    return dao.findById(new ProgramCutoff(programId,semesterId)).orElseThrow(()->new NotFoundException("No such Program Cutoff"));
  }

  @PATCH
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public ProgramCutoff updateProgramCutoff(@Auth User user, @PathParam("programId")LongParam programId, @PathParam("semesterId") LongParam semesterId, ProgramCutoff cutoff){
    if(queryBySelector.queryByProgramId(user, programId.get())) {
      return dao.update(cutoff);
    }
    throw new NotAuthorizedException("Cannot update a Program Cutoff not in your program");
  }

  @DELETE
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Status deleteProgramCutoff(@Auth User user, @PathParam("programId")LongParam programId, @PathParam("semesterId")LongParam semesterId){
    if(queryBySelector.queryByProgramId(user, programId)) {
      Status status = new Status();
      status.setId(programId.get().longValue());
      status.setAction("DELETE");
      status.setResource("ProgramCutoff");

      boolean success = dao.delete(findSafely(programId.get().longValue(), semesterId.get().longValue()));

      if (success) {
        status.setMessage("Successfully deleted Program Cutoff");
        status.setStatus(200);
      } else {
        status.setMessage("Error deleting Program Cutoff");
        status.setStatus(500);
      }
      return status;
    }
    throw new NotAuthorizedException("Cannot delete a Program Cutoff not in your program");
  }

}
