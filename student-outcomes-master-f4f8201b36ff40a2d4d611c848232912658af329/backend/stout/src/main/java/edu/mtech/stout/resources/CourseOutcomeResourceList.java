package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.CourseOutcome;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.CourseOutcomeDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.awt.*;
import java.util.List;
import java.util.Optional;

@Path("/course-outcomes")
@Produces(MediaType.APPLICATION_JSON)
public class CourseOutcomeResourceList {
  private CourseOutcomeDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private CourseDAO courseDao;

  public CourseOutcomeResourceList(CourseOutcomeDAO dao, CourseDAO courseDao ){
    this.dao = dao;
    this.courseDao = courseDao;
  }

  @POST
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public CourseOutcome createCourseOutcome(@Auth User user, CourseOutcome outcome){
    Optional<Course> c = courseDao.findById(outcome.getCourseId());
    if(c.isPresent()){
      if(queryBySelector.queryByProgramId(user,c.get().getProgramId())){
        return  dao.create(outcome);
      }
      throw new NotAuthorizedException("Cannot create course outcome not in your program");
    }else{
      throw new NotFoundException("No course outcomes are available in your program.");
    }
  }

  @GET
  @PermitAll
  @UnitOfWork
  public List<CourseOutcome> getCourseOutcomeList(@Auth User user, @QueryParam("courseId")LongParam courseId){
    Optional<Course> c = courseDao.findById(courseId.get());
    if(c.isPresent()){
      if(queryBySelector.queryByProgramId(user,c.get().getProgramId())){
        return dao.findAll();
      }
      throw new NotAuthorizedException("Cannot get course outcomes not in your program");
    }else{
      throw new NotFoundException("No course outcomes are available in your program.");
    }
  }
}
