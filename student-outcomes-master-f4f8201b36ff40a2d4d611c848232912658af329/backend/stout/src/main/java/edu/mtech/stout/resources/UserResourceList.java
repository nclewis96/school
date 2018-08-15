package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.UserApi;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.JobTitleDAO;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.RoleDAO;
import edu.mtech.stout.db.UserDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Optional;

@Path("/users")
@Produces(MediaType.APPLICATION_JSON)
public class UserResourceList {

  private UserDAO dao;
  private JobTitleDAO jobTitleDAO;
  private RoleDAO roleDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public UserResourceList(UserDAO dao, JobTitleDAO jobTitleDAO, RoleDAO roleDao) {
    this.dao = dao;
    this.jobTitleDAO = jobTitleDAO;
    this.roleDao = roleDao;
  }

  @POST
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public UserApi createUser(User user) {
    return new UserApi(Optional.of(dao.create(user)), roleDao, jobTitleDAO);
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public List<UserApi> getUserList(@Auth User user, @QueryParam("program") LongParam programId) {
    List<User> userCoreList;
    if (queryBySelector.queryByProgramId(user, programId)) {
      userCoreList = dao.findByProgramId(programId.get());
    } else {
      userCoreList = dao.findAll();
    }
    List<UserApi> apiList = new ArrayList<>();
    for (User usr : userCoreList) {
      apiList.add(new UserApi(Optional.of(usr), roleDao, jobTitleDAO));
    }
    return apiList;
  }
}
