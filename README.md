

# 2 contracts - fisheries.cpp and entities.cpp 

Although there will mulitple smart contracts between the 2 entities, we will focus on fisheries.cpp

## Fisheries
```bash
contracts/fisheries/
  fisheries.cpp
  fisheries.abi
  fisheries.wasm
  fisheries.wast
## Entities
```bash
contracts/entities/
  entities.cpp
  entities.abi
  entities.wasm
  entities.wast
```bash  
  
  usage:
  
cleos wallet create
cleos wallet open
cleos wallet unlock --password <Password>

Create account controller
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio controller <Public Key 1> <Public Key 2>

Create account authority
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio authority <Public Key 1> <Public Key 2>


Create account fisher
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio fisher <Public Key 1> <Public Key 2>


Generate wasm and abi
  eosiocpp -o fisheries/fisheries.wasm fisheries/fisheries.cpp
  eosiocpp -g fisheries/fisheries.abi fisheries/fisheries.cpp
  
assign a smart contract between authority and fishery
  cleos set contract authority /fisheries -p fisher@active
  
