package edu.mtech.stout.resources;

import edu.mtech.stout.core.Permissions;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.PermissionsDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/permissions")
@Produces(MediaType.APPLICATION_JSON)
public class PermissionsResourceList {

  private PermissionsDAO dao;

  public PermissionsResourceList(PermissionsDAO dao){
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Permissions createPermissions(Permissions permission){return dao.create(permission);}

  @GET
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public List<Permissions> getPermissions(){
    return dao.findAll();
  }



}
