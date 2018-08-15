package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Performance;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.PerformanceDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.ArrayList;
import java.util.List;

@Path("/performance-indicators")
@Produces(MediaType.APPLICATION_JSON)
public class PerformanceResourceList {

  private PerformanceDAO dao;
  private ProgramDAO programDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public PerformanceResourceList(PerformanceDAO dao, ProgramDAO programDao){
    this.programDao = programDao;
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Performance createPerformance(@Auth User user, Performance performance){
    List<Program> p = programDao.findByPerformance(performance.getId());
    if(p.size() > 0){
      Boolean hasAccess = false;
      for(int i = 0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId() )){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.create(performance);
      }else{
        throw new NotAuthorizedException("Cannot get a performance indicator not in your program");
      }
    }else{
      throw new NotFoundException("The requested performance indicator does not exist");
    }


  }

  @GET
  @PermitAll
  @UnitOfWork
  public List<Performance> getPerformance(@Auth User user, @QueryParam("progrmId") LongParam programId){
    if(programId != null){
      if(queryBySelector.queryByProgramId(user, programId.get())){
        return dao.findByProgram(programId.get());
      }else{
        throw new NotAuthorizedException("Cannot get a Performance not in your program");
      }
    }else{
      //If no Query Params, return all Course Prefix the user has access to.
      ArrayList<Performance> fullList = new ArrayList<>();
      List<Program> programList = programDao.findByUser(user.getId());

      for(int i = 0; i < programList.size(); i++){
        List<Performance> tempList = dao.findByProgram(programList.get(i).getId());
        for(int j = 0; j < tempList.size(); j++){
          fullList.add(tempList.get(0));
        }
      }

      return fullList;
    }

  }

}
