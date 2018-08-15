package edu.mtech.stout.resources;

import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Role;
import edu.mtech.stout.db.RoleDAO;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/roles/{roleId}")
@Produces(MediaType.APPLICATION_JSON)
public class RoleResource {
  private RoleDAO dao;

  public RoleResource(RoleDAO dao){
    this.dao = dao;
  }

  @GET
  @PermitAll
  @UnitOfWork
  public Role getRole(@PathParam("roleId")LongParam roleId){
    return findSafely(roleId.get());
  }

  private Role findSafely(long roleId){
    return dao.findById(roleId).orElseThrow(()-> new NotFoundException("No such Role."));
  }

  @PATCH
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Role updateRole(@PathParam("roleId") LongParam roleId, Role role) {
    return dao.update(role);
  }

  @DELETE
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Status deleteRole(@PathParam("roleId") LongParam roleId){
    Status status = new Status();
    status.setId(roleId.get().intValue());
    status.setAction("DELETE");
    status.setResource("Role");
    boolean success = dao.delete(findSafely(roleId.get().intValue()));

    if(success){
      status.setMessage("Successfully deleted role");
      status.setStatus(200);
    }else{
      status.setMessage("Error deleting role");
      status.setStatus(500);
    }
    return status;
  }

}
