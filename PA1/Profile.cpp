#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    ((*profile).getFollowers()).insertAtTheEnd(this); 

    if(following.isEmpty()) following.insertAtTheFront(profile);
    else following.insertAtTheEnd(profile);

    /* TODO */
}

void Profile::unfollowProfile(Profile *profile) {
    following.removeNode(profile);
    ((*profile).getFollowers()).removeNode(this);
    /* TODO */
}

void Profile::createPlaylist(const std::string &playlistName) {
    Playlist *newplaylist = new Playlist(playlistName);
    (playlists).insertAtTheEnd(*newplaylist); 
    /* TODO */
}

void Profile::deletePlaylist(int playlistId) {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    while(curr -> next != first){
        if((curr -> data).getPlaylistId() == playlistId){
            playlists.removeNode(curr);
            curr = curr -> next;
            break;
        }    
        else curr = curr -> next;
    }
    if((curr -> data).getPlaylistId()) playlists.removeNode(curr);
    else ;
    /* TODO */
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    while(curr -> next != first){
        if((curr -> data).getPlaylistId() == playlistId){
            (curr -> data).addSong(song);
            curr = curr -> next;
            break;
        }
        else curr = curr -> next;
    }
    if((curr -> data).getPlaylistId() == playlistId) (curr -> data).addSong(song);
    else ;
    /* TODO */
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    while(curr -> next != first){
        if((curr -> data).getPlaylistId() == playlistId){
            (curr -> data).dropSong(song);
            curr = curr ->next;
            break;
        }
        else curr = curr -> next;    
    }
    if((curr -> data).getPlaylistId() == playlistId) (curr -> data).dropSong(song);
    else ;
    /* TODO */
}

Playlist *Profile::getPlaylist(int playlistId) {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    while(curr -> next != first){
        if((curr -> data).getPlaylistId() == playlistId) return &(curr->data);
        else curr = curr -> next;
    }
    if((curr -> data).getPlaylistId() == playlistId) return &(curr->data);
    else return NULL; 
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    
    LinkedList<Playlist *> *newplaylist = new LinkedList<Playlist *>();
    while(curr -> next != first){
        if((curr -> data).isShared()){
            if((*newplaylist).isEmpty()){
                (*newplaylist).insertAtTheFront(&(curr -> data));
                curr = curr -> next;
            }
            else{
                (*newplaylist).insertAtTheEnd(&(curr -> data));
                curr = curr -> next;
            } 
        }
        else curr = curr -> next; 
    }
    if((*newplaylist).isEmpty()) (*newplaylist).insertAtTheFront(&(curr -> data));
    else (*newplaylist).insertAtTheEnd(&(curr -> data));

    return (*newplaylist);  
    /* TODO */
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    while(curr -> next != first){
        if((curr -> data).getPlaylistId() == playlistId){
            (curr -> data).shuffle(seed);
            curr = curr -> next;
        }
        else curr = curr -> next;
    }
    if((curr -> data).getPlaylistId() == playlistId) (curr -> data).shuffle(seed);
    else ;
    /* TODO */
}

void Profile::sharePlaylist(int playlistId) {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    while(curr -> next != first){
        if((curr -> data).getPlaylistId() == playlistId){
            (curr -> data).setShared(true);
            curr = curr -> next;
            break;
        }
        else curr = curr -> next;    
    }
    if((curr -> data).getPlaylistId() == playlistId) (curr -> data).setShared(true);
    else ;
    /* TODO */
}

void Profile::unsharePlaylist(int playlistId) {
    Node<Playlist> *curr = playlists.getFirstNode();
    Node<Playlist> *first = playlists.getFirstNode();
    while(curr -> next != first){
        if((curr -> data).getPlaylistId() == playlistId){
            (curr -> data).setShared(false);
            curr = curr -> next;
            break;
        }
        else curr = curr -> next;    
    }
    if((curr -> data).getPlaylistId() == playlistId) (curr -> data).setShared(false);
    else ;
    /* TODO */
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
