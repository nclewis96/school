package edu.mtech.stout.resources;

import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Semester;
import edu.mtech.stout.core.SemesterType;
import edu.mtech.stout.db.SemesterTypeDAO;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.awt.*;

@Path("/semester-types/{typeId}")
@Produces(MediaType.APPLICATION_JSON)
public class SemesterTypeResource {
  private SemesterTypeDAO dao;

  public SemesterTypeResource(SemesterTypeDAO dao){
    this.dao = dao;
  }

  @GET
  @RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public SemesterType getSemesterType(@PathParam("typeId")LongParam typeId){
    return  findSafely(typeId.get());
  }

  private SemesterType findSafely(long typeId){
    return dao.findById(typeId).orElseThrow(() -> new NotFoundException("No such Semester Type"));
  }

  @PATCH
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public SemesterType updateSemesterType(@PathParam("typeId") LongParam typeId, SemesterType type){
    return dao.update(type);
  }

  @DELETE
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Status deleteSemesterType(@PathParam("typeId") LongParam typeId){
    Status status = new Status();
    status.setId(typeId.get().intValue());
    status.setAction("DELETE");
    status.setResource("SemesterType");

    boolean success = dao.delete(findSafely(typeId.get().intValue()));

    if(success){
      status.setMessage("Successfully deleted Semester Type");
      status.setStatus(200);
    }else {
      status.setMessage("Error deleting Semester Type");
      status.setStatus(500);
    }
    return status;
  }

}
