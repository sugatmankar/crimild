MESSAGE( "-- Configuring scripting library" )

SET( CRIMILD_LIBRARY_NAME scripting )

ADD_SUBDIRECTORY( src )

IF ( CRIMILD_ENABLE_TESTS )
	ADD_SUBDIRECTORY( test )
ENDIF ( CRIMILD_ENABLE_TESTS )

