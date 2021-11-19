#pragma once

#ifndef PRINTA_PRE
#define PRINTA_PRE() fmt::print( " <" );
#endif

#ifndef PRINTA_POST
#define PRINTA_POST() fmt::print( "> " );
#endif

#ifndef LOG_PRE
#define LOG_PRE() fmt::print( " (" );
#endif  

#ifndef LOG_POST
#define LOG_POST() fmt::print( ") " );
#endif  

#define _return() std::getchar(); std::getchar();

 
