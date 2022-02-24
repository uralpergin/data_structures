#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    Profile *p = new Profile(email,username,plan);
    
    profiles.insertAtTheEnd(*p);
    /* TODO */
}

void MusicStream::deleteProfile(const std::string &email) {
    Node<Profile> *prfl = profiles.getFirstNode();
    Node<Profile> *first = prfl;
    Node<Profile> *del;

    while(prfl -> next != first){
        if((prfl -> data).getEmail() == email){
            del = prfl;
            //first
            Node<Profile *> *delprfl = ((prfl -> data).getFollowers()).getFirstNode();
            Node<Profile *> *frstflwr = delprfl;

            while(delprfl -> next != frstflwr){
                Node<Profile *> *tmp = ((*(delprfl -> data)).getFollowings()).getFirstNode();
                Node<Profile *> *frst = tmp;

                while(tmp -> next != frst){
                    if((*(tmp -> data)) == prfl -> data){
                        (*(delprfl -> data)).unfollowProfile((tmp -> data));
                        tmp = tmp -> next;
                        break;
                    }    
                    else tmp = tmp -> next;
                }
                if((*(tmp -> data)) == prfl -> data) (*(delprfl -> data)).unfollowProfile((tmp -> data));

                delprfl = delprfl -> next;        
            }
            //first last check
            Node<Profile *> *tmp = ((*(delprfl -> data)).getFollowings()).getFirstNode();
            Node<Profile *> *frst = tmp;

            while(tmp -> next != frst){
                if((*(tmp -> data)) == prfl -> data){
                    (*(delprfl -> data)).unfollowProfile((tmp -> data));
                    tmp = tmp -> next;
                    break;
                }    
                else tmp = tmp -> next;
            }
            if((*(tmp -> data)) == prfl -> data) (*(delprfl -> data)).unfollowProfile((tmp -> data));

            
            //second
            Node<Profile *> *sil = ((prfl -> data).getFollowings()).getFirstNode();
            Node<Profile *> *ilk = sil;

            while(sil -> next != ilk){
                Node<Profile *> *tmp1 = ((*(sil -> data)).getFollowers()).getFirstNode();
                Node<Profile *> *frst1 = tmp1;

                while(tmp1 -> next != frst1){
                    if((*(tmp1 -> data)) == prfl -> data){
                        (*(sil -> data)).unfollowProfile((tmp1 -> data));
                        tmp1 = tmp1 -> next;
                        break;
                    }    
                    else tmp1 = tmp1 -> next;
                }
                if((*(tmp1 -> data)) == prfl -> data) (*(sil -> data)).unfollowProfile((tmp1 -> data));

                sil = sil -> next;        
            }
            //second finish
            //second last check
            Node<Profile *> *tmp1 = ((*(sil -> data)).getFollowers()).getFirstNode();
            Node<Profile *> *frst1 = tmp1;

            while(tmp1 -> next != frst1){
                if((*(tmp1 -> data)) == prfl -> data){
                    (*(sil -> data)).unfollowProfile((tmp1 -> data));
                    tmp1 = tmp1 -> next;
                    break;
                }    
                else tmp1 = tmp1 -> next;
            }
            if((*(tmp1 -> data)) == prfl -> data) (*(sil -> data)).unfollowProfile((tmp1 -> data));

            
        }
        else prfl = prfl -> next;
    }
    if((prfl -> data).getEmail() == email){
        del = prfl;
        //first
        Node<Profile *> *delprfl = ((prfl -> data).getFollowers()).getFirstNode();
        Node<Profile *> *frstflwr = delprfl;

        while(delprfl -> next != frstflwr){
            Node<Profile *> *tmp = ((*(delprfl -> data)).getFollowings()).getFirstNode();
            Node<Profile *> *frst = tmp;

            while(tmp -> next != frst){
                if((*(tmp -> data)) == prfl -> data){
                    (*(delprfl -> data)).unfollowProfile((tmp -> data));
                    tmp = tmp -> next;
                    break;
                }    
                else tmp = tmp -> next;
            }
            if((*(tmp -> data)) == prfl -> data) (*(delprfl -> data)).unfollowProfile((tmp -> data));

            delprfl = delprfl -> next;        
        }
        //first last check
        Node<Profile *> *tmp = ((*(delprfl -> data)).getFollowings()).getFirstNode();
        Node<Profile *> *frst = tmp;

        while(tmp -> next != frst){
            if((*(tmp -> data)) == prfl -> data){
                (*(delprfl -> data)).unfollowProfile((tmp -> data));
                tmp = tmp -> next;
                break;
            }    
            else tmp = tmp -> next;
        }
        if((*(tmp -> data)) == prfl -> data) (*(delprfl -> data)).unfollowProfile((tmp -> data));

            
        //second
        Node<Profile *> *sil = ((prfl -> data).getFollowings()).getFirstNode();
        Node<Profile *> *ilk = sil;

        while(sil -> next != ilk){
            Node<Profile *> *tmp1 = ((*(sil -> data)).getFollowers()).getFirstNode();
            Node<Profile *> *frst1 = tmp1;

            while(tmp1 -> next != frst1){
                if((*(tmp1 -> data)) == prfl -> data){
                    (*(sil -> data)).unfollowProfile((tmp1 -> data));
                    tmp1 = tmp1 -> next;
                    break;
                }    
                else tmp1 = tmp1 -> next;
            }
            if((*(tmp1 -> data)) == prfl -> data) (*(sil -> data)).unfollowProfile((tmp1 -> data));

            sil = sil -> next;        
        }
        //second finish
        //second last check
        Node<Profile *> *tmp1 = ((*(sil -> data)).getFollowers()).getFirstNode();
        Node<Profile *> *frst1 = tmp1;

        while(tmp1 -> next != frst1){
            if((*(tmp1 -> data)) == prfl -> data){
                (*(sil -> data)).unfollowProfile((tmp1 -> data));
                tmp1 = tmp1 -> next;
                break;
            }    
            else tmp1 = tmp1 -> next;
        }
        if((*(tmp1 -> data)) == prfl -> data) (*(sil -> data)).unfollowProfile((tmp1 -> data));
      
    }
    
    profiles.removeNode(del);

    /* TODO */
}

void MusicStream::addArtist(const std::string &artistName) {
    Artist *artist = new Artist(artistName);

    artists.insertAtTheEnd(*artist);
    /* TODO */
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    Album *album = new Album(albumName);

    albums.insertAtTheEnd(*album);

    Node<Artist> *curr = artists.getFirstNode();
    Node<Artist> *frst = curr;
    while(curr -> next != frst){
        if((curr -> data).getArtistId() == artistId){
            (curr -> data).addAlbum(album);
            curr = curr -> next;
            break;
        }
        else curr = curr -> next;
    }
    if((curr -> data).getArtistId() == artistId) (curr -> data).addAlbum(album);
    else ;
    /* TODO */
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    Song *song = new Song(songName, songDuration);

    songs.insertAtTheEnd(*song);

    Node<Album> *curr = albums.getFirstNode();
    Node<Album> *frst = curr;
    while(curr -> next != frst){
        if((curr -> data).getAlbumId() == albumId){
            (curr -> data).addSong(song);
            curr = curr -> next;

            break;
        }
        else curr = curr -> next;
    }
    if((curr -> data).getAlbumId() == albumId) (curr -> data).addSong(song);
    
    

    /* TODO */
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    Node<Profile> *curr = profiles.getFirstNode();
    Node<Profile> *frst = curr;
    
    Profile *prof1;
    Profile *prof2;

    while(curr -> next != frst){
        if((curr -> data).getEmail() == email1) prof1 = &(curr -> data);
        if((curr -> data).getEmail() == email2) prof2 = &(curr -> data);
        curr = curr -> next;
    }
    if((curr -> data).getEmail() == email1) prof1 = &(curr -> data);
    if((curr -> data).getEmail() == email2) prof2 = &(curr -> data);

    (*prof1).followProfile(prof2);
    /* TODO */
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    Node<Profile> *curr = profiles.getFirstNode();
    Node<Profile> *frst = curr;
    
    Profile *prof1;
    Profile *prof2;

    while(curr -> next != frst){
        if((curr -> data).getEmail() == email1) prof1 = &(curr -> data);
        if((curr -> data).getEmail() == email2) prof2 = &(curr -> data);
        curr = curr -> next;
    }
    if((curr -> data).getEmail() == email1) prof1 = &(curr -> data);
    if((curr -> data).getEmail() == email2) prof2 = &(curr -> data);

    (*prof1).unfollowProfile(prof2);
    /* TODO */
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    Node<Profile> *curr = profiles.getFirstNode();
    Node<Profile> *frst = curr;

    while(curr -> next != frst){
        if((curr -> data).getEmail() == email){
            (curr -> data).createPlaylist(playlistName);
            curr = curr -> next;
            break;
        }
        else curr = curr -> next;
    }
    if((curr -> data).getEmail() == email){
        (curr -> data).createPlaylist(playlistName);
        curr = curr -> next;
    }
    /* TODO */
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *curr = profiles.getFirstNode();
    Node<Profile> *frst = curr;

    while(curr -> next != frst){
        if((curr -> data).getEmail() == email){
            (curr -> data).deletePlaylist(playlistId);
            curr = curr -> next;
            break;
        }
        else curr = curr -> next;
    }
    if((curr -> data).getEmail() == email){
        (curr -> data).deletePlaylist(playlistId);
        curr = curr -> next;
    }
    /* TODO */
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Song> *song = songs.getFirstNode();
    Node<Song> *frst = song;

    Song *thesong;
    while(song -> next != frst){
        if((song -> data).getSongId() == songId){
            thesong = &(song -> data);
            song = song -> next;
            break; 
        }
        else song = song -> next;
    }
    if((song -> data).getSongId() == songId) thesong = &(song -> data);

    Node<Profile> *profile = profiles.getFirstNode();
    Node<Profile> *first = profile;

    while(profile -> next != first){
        if((profile -> data).getEmail() == email){
            (profile -> data).addSongToPlaylist(thesong, playlistId);
            profile = profile -> next;
            break;
        }
        else profile = profile -> next;
    }
    if((profile -> data).getEmail() == email) (profile -> data).addSongToPlaylist(thesong, playlistId);

    /* TODO */
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Song> *song = songs.getFirstNode();
    Node<Song> *frst = song;

    Song *thesong;
    while(song -> next != frst){
        if((song -> data).getSongId() == songId){
            thesong = &(song -> data);
            song = song -> next;
            break; 
        }
        else song = song -> next;
    }
    if((song -> data).getSongId() == songId) thesong = &(song -> data);

    Node<Profile> *profile = profiles.getFirstNode();
    Node<Profile> *first = profile;

    while(profile -> next != first){
        if((profile -> data).getEmail() == email){
            (profile -> data).deleteSongFromPlaylist(thesong, playlistId);
            profile = profile -> next;
            break;
        }
        else profile = profile -> next;
    }
    if((profile -> data).getEmail() == email) (profile -> data).deleteSongFromPlaylist(thesong, playlistId);
    /* TODO */
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    Node<Profile> *profile = profiles.getFirstNode();
    Node<Profile> *first = profile;

    LinkedList<Song *> *newplaylist = new LinkedList<Song *>();
    while(profile -> next != first){
        if((profile -> data).getEmail() == email){
            if((profile -> data).getPlan() == 1){
                (*newplaylist) = (*playlist).getSongs();
                return (*newplaylist);    
            }
            else{
                (*newplaylist) = (*playlist).getSongs();
                (*newplaylist).insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);
                return (*newplaylist);
            }       
        }
        else profile = profile -> next;
    }
    if((profile -> data).getEmail() == email){
        if((profile -> data).getPlan() == 1){
            (*newplaylist) = (*playlist).getSongs();
            return (*newplaylist);    
        }
        else{
            (*newplaylist) = (*playlist).getSongs();
            (*newplaylist).insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);
            return (*newplaylist);
        }       
    }
    else return (*newplaylist);
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    Node<Profile> *prof = profiles.getFirstNode();
    Node<Profile> *frst = prof;

    while(prof -> next != frst){
        if((prof -> data).getEmail() == email){
            return (prof -> data).getPlaylist(playlistId);
        }
        else prof = prof -> next;
    }
    if((prof -> data).getEmail() == email){
        return (prof -> data).getPlaylist(playlistId);
    }
    else return NULL;
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    Node<Profile> *prof = profiles.getFirstNode();
    Node<Profile> *frst = prof;

    while(prof -> next != frst){
        if((prof -> data).getEmail() == email){
            return (prof -> data).getSharedPlaylists();
        }
        else prof = prof -> next;
    }
    if((prof -> data).getEmail() == email){
        return (prof -> data).getSharedPlaylists();
    }
    else{
        LinkedList<Playlist *> *newplaylist = new LinkedList<Playlist *>();
        return (*newplaylist);     
    }
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    Node<Profile> *prof = profiles.getFirstNode();
    Node<Profile> *frst = prof;

    while(prof -> next != frst){
        if((prof -> data).getEmail() == email){
            ((prof -> data).getPlaylist(playlistId))->shuffle(seed);
            prof = prof -> next;
            break;
        }
        else prof = prof -> next;
    }
    if((prof -> data).getEmail() == email){
        ((prof -> data).getPlaylist(playlistId))->shuffle(seed);   
    }
    else ;
    /* TODO */
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *prof = profiles.getFirstNode();
    Node<Profile> *frst = prof;

    while(prof -> next != frst){
        if((prof -> data).getEmail() == email){
            ((prof -> data).getPlaylist(playlistId))->setShared(1);
            prof = prof -> next;
            break;
        }
        else prof = prof -> next;
    }
    if((prof -> data).getEmail() == email){
        ((prof -> data).getPlaylist(playlistId))->setShared(1);                      
    }
    else ;
    /* TODO */
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *prof = profiles.getFirstNode();
    Node<Profile> *frst = prof;

    while(prof -> next != frst){
        if((prof -> data).getEmail() == email){
            ((prof -> data).getPlaylist(playlistId))->setShared(0);
            prof = prof -> next;
            break;
        }
        else prof = prof -> next;
    }
    if((prof -> data).getEmail() == email){
        ((prof -> data).getPlaylist(playlistId))->setShared(0);                      
    }
    else ;
    /* TODO */
}

void MusicStream::subscribePremium(const std::string &email) {
    Node<Profile> *prof = profiles.getFirstNode();
    Node<Profile> *frst = prof;

    while(prof -> next != frst){
        if((prof -> data).getEmail() == email){
            (prof -> data).setPlan(premium);
            prof = prof -> next;
            break;
        }
        else prof = prof -> next;
    }
    if((prof -> data).getEmail() == email) (prof -> data).setPlan(premium);
    else;
    /* TODO */
}

void MusicStream::unsubscribePremium(const std::string &email) {
    Node<Profile> *prof = profiles.getFirstNode();
    Node<Profile> *frst = prof;

    while(prof -> next != frst){
        if((prof -> data).getEmail() == email){
            (prof -> data).setPlan(free_of_charge);
            prof = prof -> next;
            break;
        }
        else prof = prof -> next;
    }
    if((prof -> data).getEmail() == email) (prof -> data).setPlan(free_of_charge);
    else;
    /* TODO */
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
