/** @file ToyBox.cpp */

template < class ItemType > ToyBox < ItemType >::ToyBox ()
{
  PlainBox < ItemType > ();
  boxColor = BLACK;
}   // end default constructor

template < class ItemType > ToyBox < ItemType >::ToyBox (const Color & theColor)
{
  PlainBox < ItemType > ();
  boxColor = theColor;
}   // end constructor

template < class ItemType > ToyBox < ItemType >::ToyBox (const ItemType & theItem, const Color & theColor)
  PlainBox <
ItemType > ();

PlainBox < ItemType >::setItem (theItem);
boxColor = theColor;
}   // end constructor

template < class ItemType > Color ToyBox < ItemType >::getColor () constconst
{
  return boxColor;
}   // end getColor