package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.CourseOutcome;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.CourseOutcomeDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;
import java.util.Optional;

@Path("course-outcomes/{courseId}/{outcomeId}")
@Produces(MediaType.APPLICATION_JSON)
public class CourseOutcomeResource {
  private CourseOutcomeDAO dao;
  private CourseDAO courseDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public CourseOutcomeResource(CourseOutcomeDAO dao, CourseDAO courseDao){
    this.dao = dao;
    this.courseDao = courseDao;
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public CourseOutcome getCourseOutcome(@Auth User user, @PathParam("courseId")LongParam courseId, @PathParam("outcomeId") LongParam outcomeId) {
      Optional<Course> c = courseDao.findById(courseId.get());
      if(c.isPresent()){
        if(queryBySelector.queryByProgramId(user,c.get().getProgramId())){
          return findSafely(courseId.get(), outcomeId.get());
        }
        throw new NotAuthorizedException("Cannot get course outcome not in your program");
      }else{
        throw new NotFoundException("No course outcomes are available in your program.");
      }


  }

  private CourseOutcome findSafely(long courseId, long outcomeId){
    return dao.findById(new CourseOutcome(courseId, outcomeId)).orElseThrow(() -> new NotFoundException("No such Course Outcome"));
  }

  @PATCH
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public CourseOutcome updateCourseOutcome(@Auth User user, @PathParam("courseId") LongParam courseId, @PathParam("outcomeId") LongParam outcomeId, CourseOutcome outcome){
    Optional<Course> c = courseDao.findById(courseId.get());
    if(c.isPresent()){
      if(queryBySelector.queryByProgramId(user,c.get().getProgramId())){
        return dao.update(outcome);
      }
      throw new NotAuthorizedException("Cannot update course outcome not in your program");
    }else{
      throw new NotFoundException("No course outcomes are available in your program.");
    }
  }

  @DELETE
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public Status deleteCourseOutcome(@Auth User user, @PathParam("courseId")LongParam courseId, @PathParam("outcomeId")LongParam outcomeId){
    Optional<Course> c = courseDao.findById(courseId.get());
    if(c.isPresent()){
      if(queryBySelector.queryByProgramId(user,c.get().getProgramId())){
        Status status = new Status();
        status.setId(courseId.get().longValue());
        status.setAction("DELETE");
        status.setResource("CourseOutcome");

        boolean success = dao.delete(findSafely(courseId.get().longValue(), outcomeId.get().longValue()));

        if(success){
          status.setMessage("Successfully deleted Course Outcome");
          status.setStatus(200);
        }else{
          status.setMessage("Error deleting Course Outcome");
          status.setStatus(500);
        }
        return status;
      }
      throw new NotAuthorizedException("Cannot delete course outcome not in your program");
    }else{
      throw new NotFoundException("No course outcomes are available in your program.");
    }


  }
}
