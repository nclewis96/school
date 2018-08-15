package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.OfferingOutcome;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.OfferingOutcomeDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("offering-outcomes/{offeringId}/{outcomeId}")
@Produces(MediaType.APPLICATION_JSON)
public class OfferingOutcomeResource {

  private OfferingOutcomeDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramDAO programDao;


  public OfferingOutcomeResource(OfferingOutcomeDAO dao, ProgramDAO programDAO){
    this.dao = dao;
    this.programDao = programDAO;
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OfferingOutcome getOfferingOutcome(@Auth User user, @PathParam("offeringId")LongParam offeringId, @PathParam("outcomeId") LongParam outcomeId){
    List<Program> p = programDao.findByOffering(offeringId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(offeringId.get(), outcomeId.get());
      }else{
        throw new NotAuthorizedException("Cannot get a offering outcome not in your program");
      }
    }else{
      throw new NotFoundException("No offering outcomes are available with that Id");
    }
  }

  private OfferingOutcome findSafely(long offeringId, long outcomeId){
    return dao.findById(new OfferingOutcome(offeringId, outcomeId)).orElseThrow(() -> new NotFoundException("No such Offering Outcome"));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OfferingOutcome updateOfferingOutcome(@Auth User user, @PathParam("offeringId") LongParam offeringId, @PathParam("outcomeId") LongParam outcomeId, OfferingOutcome offeringOutcome){
    List<Program> p = programDao.findByOffering(offeringId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(offeringOutcome);
      }else{
        throw new NotAuthorizedException("Cannot update a offering outcome not in your program");
      }
    }else{
      throw new NotFoundException("No offering outcomes are available with that Id");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Status deleteOfferingOutcome(@Auth User user, @PathParam("offeringId")LongParam offeringId, @PathParam("outcomeId")LongParam outcomeId){
    List<Program> p = programDao.findByOffering(offeringId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(offeringId.get().longValue());
        status.setAction("DELETE");
        status.setResource("StudentAssign");

        boolean success = dao.delete(findSafely(offeringId.get().longValue(), outcomeId.get().longValue()));

        if(success){
          status.setMessage("Successfully deleted Offering Outcome");
          status.setStatus(200);
        }else{
          status.setMessage("Error deleting Student Offering Outcome");
          status.setStatus(500);
        }
        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete a offering outcome not in your program");
      }
    }else{
      throw new NotFoundException("No offering outcomes are available with that Id");
    }

  }
}
