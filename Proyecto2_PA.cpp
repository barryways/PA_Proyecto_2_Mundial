#include "pch.h"
#include "LinkedList.h"
#include "List.h"
#include <iostream>
#include "AlbumReader.h"

using namespace System;

int main()
{
    AlbumReader* Panini_2022 = new AlbumReader();
    Panini_2022->read_album("album.csv");



    return 0;
}
