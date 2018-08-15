package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.Scale;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.ScaleDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.ArrayList;
import java.util.List;

@Path("/scales")
@Produces(MediaType.APPLICATION_JSON)
public class ScaleResourceList {

  private ScaleDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramDAO programDao;

  public ScaleResourceList(ScaleDAO dao, ProgramDAO programDao) {
    this.dao = dao;
    this.programDao = programDao;
  }

  @POST
  @RolesAllowed({"Program Coordinator","Faculty"})
  @UnitOfWork
  public Scale createScale(@Auth User user, Scale scale) {
    if(queryBySelector.queryByProgramId(user, scale.getProgId()))
      return dao.create(scale);
    throw new NotAuthorizedException("You cannot create a Scale not in your Program");
  }

  @GET
  @RolesAllowed({"Program Coordinator","Faculty"})
  @UnitOfWork
  public List<Scale> getScaleList(@Auth User user, @QueryParam("programId")LongParam programId) {
    if(programId != null){
      if(queryBySelector.queryByProgramId(user, programId.get())){
        return dao.findByProgram(programId.get());
      }else{
        throw new NotAuthorizedException("Cannot get scales not in your program");
      }
    }else if (queryBySelector.getUserPerm(user) == 2){
      //If no Query Params and is a program coordinator,
      // return all Course Prefix the user has access to.
      ArrayList<Scale> fullList = new ArrayList<>();
      List<Program> programList = programDao.findByUser(user.getId());

      for(int i = 0; i < programList.size(); i++){
        List<Scale> tempList = dao.findByProgram(programList.get(i).getId());
        for(int j = 0; j < tempList.size(); j++){
          fullList.add(tempList.get(0));
        }
      }
      return fullList;

    }else{
      //If no Query Params, return all Course Prefix the user has access to.
      ArrayList<Scale> fullList = new ArrayList<>();
      List<Program> programList = programDao.findByUser(user.getId());

      for(int i = 0; i < programList.size(); i++){
        List<Scale> tempList = dao.findByProgram(programList.get(i).getId());
        for(int j = 0; j < tempList.size(); j++){
          fullList.add(tempList.get(0));
        }
      }
      return fullList;

    }

  }

}
