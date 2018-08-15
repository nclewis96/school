package edu.mtech.stout.resources;

import edu.mtech.stout.core.SemesterType;
import edu.mtech.stout.db.SemesterTypeDAO;
import io.dropwizard.hibernate.UnitOfWork;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/semester-types")
@Produces(MediaType.APPLICATION_JSON)
public class SemesterTypeResourceList {

  private SemesterTypeDAO dao;

  public SemesterTypeResourceList(SemesterTypeDAO dao){
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public SemesterType createSemesterType(SemesterType type){
    return  dao.create(type);
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public  List<SemesterType> getSemesterTypeList(){
    return dao.findAll();
  }
}
