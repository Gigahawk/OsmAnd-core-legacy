#ifndef _OSMAND_TRANSPORT_ROUTE_STOPS_READER_H
#define _OSMAND_TRANSPORT_ROUTE_STOPS_READER_H

#include "CommonCollections.h"
#include "commonOsmAndCore.h"
// #include <queue> //check

struct BinaryMapFile;
struct SearchQuery;
struct TransportStop;
struct TransportRoute;
struct Way;

const static int MISSING_STOP_SEARCH_RADIUS = 15000;

struct TransportRouteStopsReader {
	TransportRouteStopsReader(vector<BinaryMapFile*>& files);

	UNORDERED(map)<int64_t, SHARED_PTR<TransportRoute>> combinedRoutesCache;
	UNORDERED(map)<BinaryMapFile*, UNORDERED(map)<int64_t, SHARED_PTR<TransportRoute>>> routesFileCache;

	vector<SHARED_PTR<TransportStop>> readMergedTransportStops(SearchQuery& sr);
	UNORDERED(map)<int32_t, SHARED_PTR<TransportRoute>> mergeTransportStops(BinaryMapFile* file,
																			UNORDERED(map) < int64_t, SHARED_PTR<TransportStop>> &loadedTransportStops,
																			vector<SHARED_PTR<TransportStop>> &stops);

	void putAll(UNORDERED(map)<int32_t, SHARED_PTR<TransportRoute>>& routesToLoad, int referenceToRoutes[]);
	void loadRoutes(BinaryMapFile* file, UNORDERED(map)<int32_t, SHARED_PTR<TransportRoute>>& localFileRoutes);
	SHARED_PTR<TransportRoute> getCombinedRoute(SHARED_PTR<TransportRoute> route);
	SHARED_PTR<TransportRoute> combineRoute(SHARED_PTR<TransportRoute> route);
	vector<SHARED_PTR<TransportStop>> findAndDeleteMinDistance(double lat, double lon, 
																vector<vector<SHARED_PTR<TransportStop>>>& mergedSegments, 
																bool attachToBegin);
	vector<Way> getAllWays(vector<SHARED_PTR<TransportRoute>>& parts);
	vector<vector<SHARED_PTR<TransportStop>>> combineSegmentsOfSameRoute(vector<vector<SHARED_PTR<TransportStop>>>& segments);
	vector<vector<SHARED_PTR<TransportStop>>> mergeSegments(vector<SHARED_PTR<TransportStop>>& segments, 
															vector<SHARED_PTR<TransportStop>>& resultSegments, 
															bool mergeMissingStops);
	bool tryToMerge(vector<SHARED_PTR<TransportStop>>& firstSegment, vector<SHARED_PTR<TransportStop>>& segmentToMerge);
	bool tryToMergeMissingStops(vector<SHARED_PTR<TransportStop>>& firstSegment, vector<SHARED_PTR<TransportStop>>& segmentToMerge);
	vector<vector<SHARED_PTR<TransportStop>>> parseRoutePartsToSegments(vector<SHARED_PTR<TransportRoute>> routeParts);
	vector<SHARED_PTR<TransportRoute>> findIncompleteRouteParts(SHARED_PTR<TransportRoute>& baseRoute);

};

#endif