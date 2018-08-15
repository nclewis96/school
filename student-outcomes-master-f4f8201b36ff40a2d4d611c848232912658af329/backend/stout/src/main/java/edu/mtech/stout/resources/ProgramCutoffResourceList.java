package edu.mtech.stout.resources;


import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.ProgramCutoff;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramCutoffDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/program-cutoffs")
@Produces(MediaType.APPLICATION_JSON)
public class ProgramCutoffResourceList {

  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramCutoffDAO dao;

  public ProgramCutoffResourceList(ProgramCutoffDAO dao){
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public ProgramCutoff createProgramCutoff(@Auth User user, ProgramCutoff cutoff){
    if(queryBySelector.queryByProgramId(user, cutoff.getProgramId()))
      return dao.create(cutoff);
    throw new NotAuthorizedException("You cannot create a program cutoff not in your program");
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public List<ProgramCutoff> getProgramCutoffList(@Auth User user, @QueryParam("programId")LongParam programId){
    if(programId != null){
      if(queryBySelector.queryByProgramId(user, programId)){
        return dao.findByProgram(programId.get());
      }else{
        throw new NotAuthorizedException("Cannot get program cutoffs not in your program");
      }
    }
    return dao.findAll();
  }

}
