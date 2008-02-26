/*
 * repository.h -- provides a map between service and shared objects
 * Copyright (C) 2003-2004 Ushodaya Enterprises Limited
 * Author: Charles Yates <charles.yates@pandora.be>
 * Contributor: Dan Dennedy <dan@dennedy.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _MLT_REPOSITORY_H_
#define _MLT_REPOSITORY_H_

#include "mlt_types.h"
#include "mlt_profile.h"

/** Repository structure forward reference.
*/

typedef struct mlt_repository_s *mlt_repository;

/** This callback is the main entry point into a module, which must be exported
    with the symbol "mlt_register".
    Inside the callback, the module registers the additional callbacks below.
*/

typedef void ( *mlt_repository_callback )( mlt_repository );

/** These are callback functions that modules implement to construct services
    and metadata.
*/
typedef void *( *mlt_register_callback )( mlt_profile, mlt_service_type, const char * /* service name */, void * /* arg */ );
typedef mlt_properties ( *mlt_metadata_callback )( mlt_service_type, const char * /* service name */, void * /* callback_data */ );

/** These convenience macros can be used to register services in a more declarative manner.
*/
#define MLT_REPOSITORY void mlt_register( mlt_repository repository )
#define MLT_REGISTER( type, service, symbol  ) ( mlt_repository_register( repository, (type), (service), ( mlt_register_callback )(symbol) ) )
#define MLT_REGISTER_METADATA( type, service, callback, data ) ( mlt_repository_register_metadata( repository, (type), (service), ( mlt_metadata_callback )(callback), (data) ) )

/** Public functions.
*/

extern mlt_repository mlt_repository_init( const char *directory );
extern void mlt_repository_register( mlt_repository self, mlt_service_type service_type, const char *service, mlt_register_callback );
extern void *mlt_repository_create( mlt_repository self, mlt_profile profile, mlt_service_type type, const char *service, void *arg ); 
extern void mlt_repository_close( mlt_repository self );
extern mlt_properties mlt_repository_consumers( mlt_repository self );
extern mlt_properties mlt_repository_filters( mlt_repository self );
extern mlt_properties mlt_repository_producers( mlt_repository self );
extern mlt_properties mlt_repository_transitions( mlt_repository self );
extern void mlt_repository_register_metadata( mlt_repository self, mlt_service_type type, const char *service, mlt_metadata_callback, void *callback_data );
extern mlt_properties mlt_repository_metadata( mlt_repository self, mlt_service_type type, const char *service );

#endif

