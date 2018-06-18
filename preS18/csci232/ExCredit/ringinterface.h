// Nathaniel Lewis
//nlewis
//nlewis


#ifndef _RING_INTERFACE 
#define _RING_INTERFACE

template < class ItemType >
class ringinterface {
   public:
   
    /**Returns the current item in the Ring
    @returns the ItemType value of the item at the reference*/
    virtual ItemType& getCurrent();             
    
    /**Moves the reference down the ring one position, or to the top if at the end
    @post the reference is moved down 1 position */
    virtual void advance();
    
    /**Adds an item to the ring
    @pos If successful, item is added, total is increased by 1
    @param item - item to be added to the ring
    @returns true if the item is added, false if it is not*/
    virtual bool addItem(const ItemType& item);
    
    /**Removes an item from the ring
    @post If successful, item is removed, total is decreased by 1
    @param item - item to be removed from ring
    @returns true if the item is removed, false if it is not*/
    virtual bool removeItem(const ItemType& item);




}
#endif