/** @file MagicBox.cpp */
template < class ItemType > MagicBox < ItemType >::MagicBox ()
{
  PlainBox < ItemType > ();
  fi rstItemStored = false;	// Box has no magic initially
}   // end default constructor

template < class ItemType > MagicBox < ItemType >::MagicBox (const ItemType & theItem)
{
  fi rstItemStored = false;	// Box has no magic initially

  setItem (theItem);
// Box has magic now
}   // end constructor

template < class ItemType > void MagicBox < ItemType >::setItem (const ItemType & theItem)
{
  if (!fi rstItemStored)
    {
      PlainBox < ItemType >::setItem (theItem);
      fi rstItemStored = true;	// Box now has magic
    }	// end if
}   // end setItem