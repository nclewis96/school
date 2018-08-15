package edu.mtech.stout.resources;

import edu.mtech.stout.core.Semester;
import edu.mtech.stout.db.SemesterDAO;
import io.dropwizard.hibernate.UnitOfWork;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/semesters")
@Produces(MediaType.APPLICATION_JSON)
public class SemesterResourceList {

  private SemesterDAO dao;

  public SemesterResourceList(SemesterDAO dao) {
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Program Coordinator"})
  @UnitOfWork
  public Semester createSemester(Semester semester) {
    return dao.create(semester);
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public List<Semester> getSemesterList() {
    return dao.findAll();
  }

}
