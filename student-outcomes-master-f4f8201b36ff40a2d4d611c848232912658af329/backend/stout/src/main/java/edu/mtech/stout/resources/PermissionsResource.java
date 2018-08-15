package edu.mtech.stout.resources;

import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Permissions;
import edu.mtech.stout.db.PermissionsDAO;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/permissions/{permissionsId}")
@Produces(MediaType.APPLICATION_JSON)
public class PermissionsResource {

  private PermissionsDAO dao;

  public PermissionsResource(PermissionsDAO dao){this.dao = dao;}

  @GET
  @PermitAll
  @UnitOfWork
  public Permissions getPermissions(@PathParam("permissionsId") LongParam permissionsId) {return findSafely(permissionsId.get());}

  private Permissions findSafely(long permissionsId){
    return  dao.findById(permissionsId).orElseThrow(() -> new NotFoundException("No such Program Permission"));
  }

  @PATCH
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Permissions updatePermissions(@PathParam("permissionsId") LongParam permissionsId, Permissions permission){
    return dao.update(permission);
  }

  @DELETE
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Status deletePermissions(@PathParam("permissionsId") LongParam permissionsId) {
    Status status = new Status();
    status.setId(permissionsId.get().intValue());
    status.setAction("DELETE");
    status.setResource("JobTitle");

    boolean success = dao.delete(findSafely(permissionsId.get().intValue()));

    if (success) {
      status.setMessage("Successfully deleted Program Permission");
      status.setStatus(200);
    } else {
      status.setMessage("Error deleting Program Permission");
      status.setStatus(500);
    }

    return status;

  }}
