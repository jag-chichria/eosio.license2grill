#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;

class fisheries_contract : public eosio::contract {
  public:
      fisheries_contract(account_name s):
        contract(s), // initialization of the base class for the contract
        _fisher_authority(s, s) // initialize the table with code and scope NB! Look up definition of code and scope
      {
      }

      /// @abi action
      void create(account_name username, uint64_t registerationNo, const std::string& fullname, std::string address, uint64_t number) {
        require_auth(username);
        // Let's make sure the primary key doesn't exist
        // _fisher_authority.end() is in a way similar to null and it means that the value isn't found
        eosio_assert(_fisher_authority.find(registerationNo) == _fisher_authority.end(), "This registerationNo already exists in the fisheries_contract");
        _fisher_authority.emplace(get_self(), [&]( auto& p ) {
           p.registerationNo = registerationNo;
           p.fullname = fullname;
           p.address = address;  

           p.number = number;
        });
      } 

  private: 
    // Setup the struct that represents the row in the table
    /// @abi table fisher_authority
    struct authority {
      uint64_t registerationNo; // primary key, social security number
      std::string fullname;
      std::string address;
      uint64_t age;            

      uint64_t primary_key()const { return registerationNo; }   
      uint64_t by_number()const { return number; }   
    };

    // We setup the table:
    /// @abi table
    typedef eosio::multi_index< N(fisher_authority), authority, indexed_by<N(byage), const_mem_fun<authority, uint64_t, &authority::by_number>>>  fisher_authority;

    fisher_authority _fisher_authority;

};

 EOSIO_ABI( fisheries_contract, (create) )
