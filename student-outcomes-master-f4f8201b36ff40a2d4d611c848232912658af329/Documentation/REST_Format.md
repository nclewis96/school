# Backend REST formats

The backend should for all actions check that the user has the requisite permissions.
(See CRUD Matrix)

| URL | GET | PUT | POST | DELETE |
|---|---|---|---|---|
| Resources | Get a collection of the named resource. |  Replace collection. May use for set operations such as grades? | Insert a new item into the table.  | Remove whole collection. May be used if an offering with data is deleted? |
| Resource/{id} | Get a singular item based on id. | Not used. | Update a single item. | Delete the item.|

Names for files should reflect purpose.
* In the resources folder, anything doing set operations (Resources in table) should be {item}List where {item} is the data type being represented and have a path of the plural of the object. (ex. Table: Users, File: UserResourceList, Path: Users).
* In contrast for getting/changing a singular item we would have the file and path be the singular object. (ex. Table: Users, File: UserResource, Path: user/{id})

Representation Files:
* They go into `core` if they are handled by the db management.
* They go into `api` if they are manually managed.

With proper tagging and annotations either will automagically transition from Java Objects to JSON objects back and forth at the beginning and end of the request lifecycle.
