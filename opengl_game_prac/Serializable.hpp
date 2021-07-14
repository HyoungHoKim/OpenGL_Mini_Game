//
//  Serializable.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/13.
//

#ifndef Serializable_hpp
#define Serializable_hpp

#include <boost/asio.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

#include "GameLevel.hpp"

class Serializable
{
private:
    vector<bool> s_destroyed;
    Serializable() {};
public:
    Serializable(vector<bool> &_destroyed);
    
    vector<bool> &getDestroyed(void);
    void setDestroyed(vector<bool> &_destroyed);
    
    void clear_destroyed(void);

private: // serialiaztion
    friend class boost::serialization::access;
    template< class Archive >
    void serialize( Archive& ar, unsigned int version )
    {
        ar & s_destroyed;
    }
};

#endif /* Serializable_hpp */
