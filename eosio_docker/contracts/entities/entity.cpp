#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;

class entities : public eosio::contract {
public:
  entities(account_name s):
        contract(s), // initialization of the base class for the contract
        _accentity(s, s) // initialize the table with code and scope NB! Look up definition of code and scope
        {
        }

      /// @abi action
        void create(account_name username, uint64_t registerationNo, const std::string& fullname, const std::string& address, 
          const std::string& directors, const std::string& fishingConditions, const std::string& registeredBoats,
          const std::string& devices, const std::string& quotaEntitlment, const std::string& exemptions, const std::string& entityType, 
          uint64_t number) {
          require_auth(username);
        // Let's make sure the primary key doesn't exist
        // _accentity.end() is in a way similar to null and it means that the value isn't found
          eosio_assert(_accentity.find(registerationNo) == _accentity.end(), "This registerationNo already exists in the entities");
          _accentity.emplace(get_self(), [&]( auto& p ) {
           p.registerationNo = registerationNo;
           p.fullname = fullname;
           p.address = address;
           p.directors = directors;
           p.fishingConditions = fishingConditions;
           p.registeredBoats  =registeredBoats;
           p.devices = devices;
           p.quotaEntitlment = quotaEntitlment;
           p.exemptions =exemptions;
           p.entityType  = entityType;           
           p.number = number;
         });
        }

      /// @abi action
        void update( account_name username, uint64_t registerationNo, const std::string& fullname, const std::string& address, 
          const std::string& directors, const std::string& fishingConditions, const std::string& registeredBoats,
          const std::string& devices, const std::string& quotaEntitlment, const std::string& exemptions, const std::string& entityType,
          uint64_t number ) {
      // validating permissions
          require_auth( username );

    // get accentity by registerationNo
          auto accentity_itr = _accentity.find(registerationNo);
    // check if the object exists
          eosio_assert(accentity_itr != _accentity.end(), "No entity was not found");
    // update object
          _accentity.modify( accentity_itr, username, [&]( auto& p ) {
            p.registerationNo = registerationNo;
           p.fullname = fullname;
           p.address = address;
           p.directors = directors;
           p.fishingConditions = fishingConditions;
           p.registeredBoats  =registeredBoats;
           p.devices = devices;
           p.quotaEntitlment = quotaEntitlment;
           p.exemptions =exemptions;
           p.entityType  = entityType;           
           p.number = number;
          });
        } 

      private: 
    // Setup the struct that represents the row in the table
    /// @abi table accentity
        struct entity  {
      uint64_t registerationNo; // primary key, social security number
      std::string fullname;
      std::string address;
      std::string directors;
      std::string fishingConditions;
      std::string registeredBoats;
      std::string devices; 
      std::string quotaEntitlment;
      std::string exemptions;
      std::string entityType;
      uint64_t number;

      uint64_t primary_key()const { return registerationNo; }
      uint64_t by_number()const { return number; }
    };

    // We setup the table:
    /// @abi table
    typedef eosio::multi_index< N(accentity), entity , indexed_by<N(bynumber), const_mem_fun<entity , uint64_t, &entity ::by_number>>>  accentity;

    accentity _accentity;

  };

  EOSIO_ABI( entities, (create)(update) )