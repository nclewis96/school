package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Role;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.RoleDAO;
import io.dropwizard.hibernate.UnitOfWork;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/roles")
@Produces(MediaType.APPLICATION_JSON)
public class RoleResourceList {
  private RoleDAO dao;


  public RoleResourceList(RoleDAO dao){
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Role createRole(Role role){
    return dao.create(role);
  }

  @GET
  @PermitAll
  @UnitOfWork
  public List<Role> getRoleList(){
    return dao.findAll();
  }


}
