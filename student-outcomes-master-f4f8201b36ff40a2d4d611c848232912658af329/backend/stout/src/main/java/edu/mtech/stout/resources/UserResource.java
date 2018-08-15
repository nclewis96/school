package edu.mtech.stout.resources;

import edu.mtech.stout.api.Status;
import edu.mtech.stout.api.UserApi;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.JobTitleDAO;
import edu.mtech.stout.db.RoleDAO;
import edu.mtech.stout.db.UserDAO;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.Optional;

@Path("/users/{userId}")
@Produces(MediaType.APPLICATION_JSON)
public class UserResource {

  private UserDAO dao;
  private RoleDAO roleDao;
  private JobTitleDAO jobTitleDAO;

  public UserResource(UserDAO dao, JobTitleDAO jobTitleDAO, RoleDAO roleDao) {
    this.dao = dao;
    this.jobTitleDAO = jobTitleDAO;
    this.roleDao = roleDao;
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public UserApi getUser(@PathParam("userId") LongParam userId) {
    Optional<User> user;
    user = Optional.of(findSafely(userId.get()));
    return new UserApi(user, roleDao, jobTitleDAO);
  }

  private User findSafely(long userId) {
    return dao.findById(userId).orElseThrow(() -> new NotFoundException("No such user."));
  }

  @PATCH
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public User updateUser(@PathParam("userId") LongParam userId, User user) {
    return dao.update(user);
  }

  @DELETE
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Status deleteUser(User user) {
    Status status = new Status();
    status.setId(user.getId());
    status.setAction("DELETE");
    status.setResource("User");

    boolean success = dao.delete(user);

    if (success) {
      status.setMessage("Successfully deleted user");
      status.setStatus(200);
    } else {
      status.setMessage("Error deleting user");
      status.setStatus(500);
    }
    return status;
  }

}
