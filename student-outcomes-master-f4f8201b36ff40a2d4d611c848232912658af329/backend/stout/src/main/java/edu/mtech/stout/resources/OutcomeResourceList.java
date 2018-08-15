package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.Outcome;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.OutcomeDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/outcomes")
@Produces(MediaType.APPLICATION_JSON)
public class OutcomeResourceList {

  private OutcomeDAO dao;
  private CourseDAO courseDao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private ProgramDAO programDao;

  public OutcomeResourceList(OutcomeDAO dao, ProgramDAO programDao, CourseDAO courseDao) {
    this.dao = dao;
    this.courseDao = courseDao;
    this.programDao = programDao;
  }

  @POST
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Outcome createOutcome(@Auth User user, Outcome outcome) {
    List<Course> c = courseDao.findByOutcome(outcome.getId());
    if(c.size()>0){
      Boolean hasAccess = false;
      for(int i = 0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.create(outcome);
      }else{
        throw new NotAuthorizedException("Cannot create an outcome not in your program");
      }
    }else{
      throw new NotFoundException("The outcome is not associated with any programs");
    }

  }

  @GET
  @PermitAll
  @UnitOfWork
  public List<Outcome> getOutcomeList(@Auth User user,
                                      @QueryParam("metricId")LongParam metricId,
                                      @QueryParam("programId")LongParam programId) {
    if(programId != null){
      if(queryBySelector.queryByProgramId(user, programId.get())){
        if(metricId != null){
          return dao.findByMetric(metricId.get());
        }else{
          return dao.findAll();
        }
      }
    }else{
      throw new NotAuthorizedException("Cannot get outcomes not in your program");
    }
    throw new NotFoundException("Bleh");
  }

}
