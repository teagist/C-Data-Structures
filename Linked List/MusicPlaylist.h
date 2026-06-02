//****************************************************************************
//	Header File for Music Playlist.
//	Programmed by: Houston Brown
//	Last Compiled Date: 6/2/2026
//****************************************************************************

#include "LinkedList.h"

template <class V>
class MusicPlaylist
{
public:
    MusicPlaylist();

    void addSong(const std::string& songName);
    void removeSong(const std::string& songName);
    void searchPlaylist(const std::string& songName);

    void play();
    void skipSong();
    void rewindToPrevSong();

private:
    LinkedList<V> playlist;
    bool isPlaying;
};
