

# 2 contracts - fisheries.cpp and entities.cpp 

Although there will mulitple smart contracts between the 2 entities, we will focus on fisheries.cpp

## Fisheries
```bash
contracts/fisheries/
  fisheries.cpp
  fisheries.abi
  fisheries.wasm
  fisheries.wast
```

## Entities
```bash
contracts/entities/
  entities.cpp
  entities.abi
  entities.wasm
  entities.wast
```  
  
## Usage:
```bash  
cleos wallet create
cleos wallet open
cleos wallet unlock --password <Password>
```

##Create account controller
```bash
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio controller <Public Key 1> <Public Key 2>
```


## Create account authority1
```bash
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio authority <Public Key 1> <Public Key 2>
```

## Create account authority2
```bash
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio authority <Public Key 1> <Public Key 2>
```


## Create account fisher1
```bash
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio fisher <Public Key 1> <Public Key 2>
```


## Create account fisher2
```bash
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio fisher <Public Key 1> <Public Key 2>
```


## Create account fisher3
```bash
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio fisher <Public Key 1> <Public Key 2>
```

## Generate wasm and abi
```bash
  eosiocpp -o fisheries/fisheries.wasm fisheries/fisheries.cpp
  eosiocpp -g fisheries/fisheries.abi fisheries/fisheries.cpp
```

## Assign a smart contract between authority and fishery
```bash
  cleos set contract authority /fisheries -p fisher@active
```  


## token issuer account
```bash
  cleos create key
  cleos create key
  cleos wallet import --private-key <Private Key 1>
  cleos wallet import --private-key <Private Key 2>
  cleos create account eosio  lictogrl.token <Public Key 1> <Public Key 2>
  
  cleos set contract lictogrl.token /contracts/eosio.token -p lictogrl.token
```

### this need changes to support more contract attributes how due to time constraint going ahead with the scaffold.
```bash
  cleos push action lictogrl.token create '{"issuer":"license2grill", "maximum_supply":"500000000.0000 HAK"}' -p eosio.token@active
```

### Assign new tokens to the accounts
  cleos push action lictogrl.token issue '[ "authority1", "250000.0000 HAK", "Issued today to authoriy1" ]' -p authority1
  cleos push action lictogrl.token issue '[ "authority2", "500000.0000 HAK", "Issued today to authoriy1" ]' -p authority2

