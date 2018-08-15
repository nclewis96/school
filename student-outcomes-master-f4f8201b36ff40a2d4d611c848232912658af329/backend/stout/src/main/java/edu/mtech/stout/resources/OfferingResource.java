package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Offering;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.OfferingDAO;
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

@Path("/offerings/{offeringId}")
@Produces(MediaType.APPLICATION_JSON)
public class OfferingResource {

  private OfferingDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramDAO programDao;

  public OfferingResource(OfferingDAO dao, ProgramDAO programDao) {
    this.dao = dao;
    this.programDao = programDao;
  }

  @GET
  @PermitAll
  @UnitOfWork
  public Offering getOffering(@Auth User user, @PathParam("offeringId") LongParam offeringId) {
    List<Program> p = programDao.findByOffering(offeringId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(offeringId.get());
      }else{
        throw new NotAuthorizedException("Cannot get an offering not in your program");
      }
    }else{
      throw new NotFoundException("No offerings are available with that Id");
    }
  }

  private Offering findSafely(long offeringId) {
    return dao.findById(offeringId).orElseThrow(() -> new NotFoundException("No such offering."));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Offering updateOffering(@Auth User user, @PathParam("offeringId") LongParam offeringId, Offering offering) {
    List<Program> p = programDao.findByOffering(offeringId.get());

    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(offering);
      }else{
        throw new NotAuthorizedException("Cannot update an offering not in your program");
      }
    }else{
      throw new NotFoundException("No offerings are available with that Id");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Status deleteOffering(@Auth User user, @PathParam("offeringId") LongParam offeringId) {
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
        status.setId(offeringId.get());
        status.setAction("DELETE");
        status.setResource("Offering");

        boolean success = dao.delete(findSafely(offeringId.get()));

        if (success) {
          status.setMessage("Successfully deleted offering");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting offering");
          status.setStatus(500);
        }
        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete an offering not in your program");
      }
    }else{
      throw new NotFoundException("No offerings are available with that Id");
    }

  }
}
