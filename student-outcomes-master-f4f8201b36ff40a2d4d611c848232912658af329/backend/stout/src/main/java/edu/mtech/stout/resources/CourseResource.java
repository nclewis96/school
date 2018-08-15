package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.Optional;

@Path("/courses/{courseId}")
@Produces(MediaType.APPLICATION_JSON)
public class CourseResource {

  private CourseDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public CourseResource(CourseDAO dao) {
    this.dao = dao;
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public Course getCourse(@Auth User user, @PathParam("courseId") LongParam courseId) {
    Optional<Course> c = dao.findById(courseId.get());
    if(c.isPresent()){
      if(queryBySelector.queryByProgramId(user,c.get().getProgramId())){
        return findSafely(courseId.get());
      }
      throw new NotAuthorizedException("Cannot create a course not in your program");
    }else{
      throw new NotFoundException("No courses are available in your program.");
    }
  }

  private Course findSafely(long courseId) {
    return dao.findById(courseId).orElseThrow(() -> new NotFoundException("No such course."));
  }

  @PATCH
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public Course updateCourse(@Auth User user, @PathParam("courseId") LongParam courseId, Course course) {
      if(queryBySelector.queryByProgramId(user,course.getProgramId())){
        return dao.update(course);
      }
      throw new NotAuthorizedException("Cannot create course not in your program");

  }

  @DELETE
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Status deleteCourse(@Auth User user, @PathParam("courseId") LongParam courseId) {
    Optional<Course> c = dao.findById(courseId.get());
    if(c.isPresent()){
      if(queryBySelector.queryByProgramId(user,c.get().getProgramId())){
        Status status = new Status();
        status.setId(courseId.get().intValue());
        status.setAction("DELETE");
        status.setResource("Course");

        boolean success = dao.delete(findSafely(courseId.get().intValue()));

        if (success) {
          status.setMessage("Successfully deleted course");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting course");
          status.setStatus(500);
        }
        return status;
      }
      throw new NotAuthorizedException("Cannot delete course not in your program");
    }else{
      throw new NotFoundException("No courses are available in your program.");
    }

  }
}