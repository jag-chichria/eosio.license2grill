#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;

class fishercont  : public eosio::contract {
  public:
      fishercont (account_name s):
        contract(s), // initialization of the base class for the contract
        _fisherTrans(s, s) // initialize the table with code and scope NB! Look up definition of code and scope
      {
      }

      /// @abi action
      void create(account_name username, uint64_t regNo, const std::string& estimate, std::string start_date, std::string end_date, uint64_t number) {
        require_auth(username);
        // Let's make sure the primary key doesn't exist
        // _fisherTrans.end() is in a way similar to null and it means that the value isn't found
        eosio_assert(_fisherTrans.find(regNo) == _fisherTrans.end(), "This regNo already exists in the fishercont ");
        _fisherTrans.emplace(get_self(), [&]( auto& p ) {
           p.regNo = regNo;
           p.estimate = estimate;
           p.start_date = start_date;  
           p.end_date = end_date;  

           p.number = number;
        });
      } 

  private: 
    // Setup the struct that represents the row in the table
    /// @abi table fisherTrans
    struct fisherstrct {
      uint64_t regNo; // primary key, social security number
      std::string estimate;
      std::string start_date;
      std::string end_date;
      uint64_t number;            

      uint64_t primary_key()const { return regNo; }   
      uint64_t by_number()const { return number; }   
    };

    // We setup the table:
    /// @abi table
    typedef eosio::multi_index< N(fisherTrans), fisherstrct, indexed_by<N(byage), const_mem_fun<fisherstrct, uint64_t, &fisherstrct::by_number>>>  fisherTrans;

    fisherTrans _fisherTrans;

};

 EOSIO_ABI( fishercont , (create) )
