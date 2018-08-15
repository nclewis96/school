package edu.mtech.stout.resources;

import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Semester;
import edu.mtech.stout.db.SemesterDAO;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/semesters/{semesterId}")
@Produces(MediaType.APPLICATION_JSON)
public class SemesterResource {

  private SemesterDAO dao;

  public SemesterResource(SemesterDAO dao) {
    this.dao = dao;
  }

  @GET
  @UnitOfWork
  public Semester getSemester(@PathParam("semesterId") LongParam semesterId) {
    return findSafely(semesterId.get());
  }

  private Semester findSafely(long semesterId) {
    return dao.findById(semesterId).orElseThrow(() -> new NotFoundException("No such Semester."));
  }

  @PATCH
  @UnitOfWork
  public Semester updateSemester(@PathParam("semesterId") LongParam semesterId, Semester semester) {
    return dao.update(semester);
  }

  @DELETE
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Status deleteSemester(@PathParam("semesterId") LongParam semesterId) {
    Status status = new Status();
    status.setId(semesterId.get().intValue());
    status.setAction("DELETE");
    status.setResource("Semester");

    boolean success = dao.delete(findSafely(semesterId.get().intValue()));

    if (success) {
      status.setMessage("Successfully deleted semester");
      status.setStatus(200);
    } else {
      status.setMessage("Error deleting semester");
      status.setStatus(500);
    }

    return status;
  }
}