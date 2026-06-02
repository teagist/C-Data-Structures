//****************************************************************************
//	Implementation File for Music Playlist.
//	Programmed by: Houston Brown
//	Last Compiled Date: 6/2/2026
//****************************************************************************

#include "MusicPlaylist.h"

//****************************************************************************
//	CONSTRUCTOR.
//****************************************************************************
template <class V>
MusicPlaylist<T>::MusicPlaylist()
{
    isPlaying = false;
}

//****************************************************************************
//	NAME: addSong.
//
//	DESCRIPTION: Add a song to the music playlist.
//
//	PARAMETERS:
//		songName: the name of the song to be added to the playlist.
//****************************************************************************
template <class V>
void MusicPlaylist<T>::addSong(const std::string& songName)
{
    return;
}

//****************************************************************************
//	NAME: removeSong.
//
//	DESCRIPTION: Remove a song from the music playlist.
//
//	PARAMETERS:
//		songName: the name of the song to be removed from the playlist.
//****************************************************************************
template <class V>
void MusicPlaylist<T>::removeSong(const std::string& songName)
{
    return;
}

//****************************************************************************
//	NAME: searchPlaylist.
//
//	DESCRIPTION: Search the playlist for a song.
//
//	PARAMETERS:
//		songName: the name of the song to find.
//****************************************************************************
template <class V>
void MusicPlaylist<T>::searchPlaylist(const std::string& songName)
{
    return;
}

//****************************************************************************
//	NAME: play.
//
//	DESCRIPTION: Begin playing the playlist.
//
//	PARAMETERS: N/A.
//****************************************************************************
template <class V>
void MusicPlaylist<T>::play()
{
    return;
}

//****************************************************************************
//	NAME: skipSong.
//
//	DESCRIPTION: Go to the next song in the playlist.
//
//	PARAMETERS: N/A.
//****************************************************************************
template <class V>
void MusicPlaylist<T>::skipSong()
{
    // If the list is empty, return.
    // If the list has one item, stop playing.
    // If the list has more than one item, go to the next item.
        // But if at the end of the list, go back to the front.
    return;
}

//****************************************************************************
//	NAME: rewindToPrevSong.
//
//	DESCRIPTION: Go back to the previous song in the playlist.
//
//	PARAMETERS: N/A.
//****************************************************************************
template <class V>
void MusicPlaylist<T>::rewindToPrevSong()
{
    return;
}
