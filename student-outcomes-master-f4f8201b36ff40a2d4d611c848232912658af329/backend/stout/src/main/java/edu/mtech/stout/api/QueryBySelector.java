package edu.mtech.stout.api;

import edu.mtech.stout.core.Permissions;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.PermissionsDAO;
import edu.mtech.stout.db.UserDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.jersey.params.LongParam;
import edu.mtech.stout.db.ProgramDAO;

import javax.management.Query;
import javax.ws.rs.ForbiddenException;
import javax.ws.rs.NotAuthorizedException;
import javax.ws.rs.QueryParam;
import java.util.HashSet;

public class QueryBySelector {

    private static ProgramDAO programDao;
    private static UserDAO userDao;
    private static PermissionsDAO permissionsDao;



  public static void setDAOs(ProgramDAO program, PermissionsDAO permissions, UserDAO user){
      programDao = program;
      permissionsDao = permissions;
      userDao = user;
    }

    public boolean queryByProgramId( User user, @QueryParam("programId") LongParam programId){
    HashSet<Long> programAccessList = programDao.getProgramIdSetByUser(user.getId());

    if(programId != null) {
      if (programAccessList.contains(programId.get())) {
        return true;
      }else{
        throw new NotAuthorizedException("You do not have access to that program");
      }
    }else {
      return false;
    }
  }

  public boolean queryByProgramId( User user, long programId){
    HashSet<Long> programAccessList = programDao.getProgramIdSetByUser(user.getId());
    if (programAccessList.contains(programId)) {
      return true;
    }else{
      throw new NotAuthorizedException("You do not have access to that program");
    }
  }

    //Returns a users Permission level
    public long  getUserPerm( User user){
        if(user != null){
            return permissionsDao.findByUserId(user.getId()).get(0).getPermissionId();

        }else{
            return -1;
        }
    }

    //Checks if a logged in user has the needed permissions for a program
    public boolean queryUserPermForProg(User user, long programId, long permissionId){
        if(user != null){
           Permissions userPerm = permissionsDao.findByUserId(user.getId()).get(0);
           if(userPerm.getPermissionId() == permissionId && userPerm.getProgramId() == programId){
               return true;
           }
        }
        return false;

    }
}
