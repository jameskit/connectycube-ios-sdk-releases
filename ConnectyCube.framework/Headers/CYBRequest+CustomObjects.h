//
//  CYBRequest+CustomObjects.h
//  ConnectyCube
//
//  Copyright © 2018 ConnectyCube. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ConnectyCube/CYBRequest.h>
#import <ConnectyCube/CYBCustomObjectsTypes.h>

@class CYBPaginator;
@class CYBCustomObject;
@class CYBCustomObjectFile;
@class CYBCustomObjectPermissions;
@class CYBCustomObjectFileUploadInfo;

NS_ASSUME_NONNULL_BEGIN

typedef void(^CYBCountBlock)(NSUInteger count);
typedef void(^CYBCustomObjectBlock)(CYBCustomObject *object);
typedef void(^CYBCustomObjectsBlock)(NSArray<CYBCustomObject *> *objects);
typedef void(^CYBCustomObjectsPageBlock)(NSArray<CYBCustomObject *> *objects, CYBPaginator *paginator);

@interface CYBRequest (CustomObjects)

//MARK: - Get Objects

/**
 Retrieve object with ID
 
 @param className Name of class
 @param ID Identifier of object to be retrieved
 @param successBlock Block with response instance and CYBCustomObject instance if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)objectWithClassName:(NSString *)className
                                 ID:(NSString *)ID
                       successBlock:(nullable CYBCustomObjectBlock)successBlock
                         errorBlock:(nullable CYBErrorBlock)errorBlock;

/**
 Retrieve objects with IDs
 
 @param className Name of class
 @param IDs Identifiers of objects to be retrieved
 @param successBlock Block with response instance, NSArray of found objects if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)objectsWithClassName:(NSString *)className
                                 IDs:(NSArray<NSString *> *)IDs
                        successBlock:(nullable CYBCustomObjectsBlock)successBlock
                          errorBlock:(nullable CYBErrorBlock)errorBlock;

/**
 Retrieve objects with extended Request
 
 @param className Name of class
 @param extendedRequest Extended set of request parameters. `count` parameter is ignored. To receive count use `countObjectsWithClassName:extendedRequest:successBlock:errorBlock:`
 @param successBlock Block with response instance, NSArray of found objects, NSArray of not found objects Ids and CYBPaginator if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)objectsWithClassName:(NSString *)className
                     extendedRequest:(nullable NSMutableDictionary <NSString *, NSString *> *)extendedRequest
                        successBlock:(nullable CYBCustomObjectsPageBlock)successBlock
                          errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Objects aggregated by operator

/**
 *  Returns calculated data for specified objects
 *
 *  @param className           Required. Name of class.
 *  @param aggregationOperator Required. Maximum, minimum, average or summary.
 *  @param fieldName           Required. Field name which will be used for calculation.
 *  @param groupFieldName      Required. Field name for group.
 *  @param extendedRequest     Optional. Extended set of request parameters. `count` parameter is ignored. To receive count use `countObjectsWithClassName:extendedRequest:successBlock:errorBlock:`.
 *  @param successBlock        Block with response instance, NSArray of grouped objects.
 *  @param errorBlock          Block with response instance if the request is failed.
 *
 *  @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)objectsWithClassName:(NSString *)className
                 aggregationOperator:(CYBCustomObjectAggregationOperator)aggregationOperator
                        forFieldName:(NSString *)fieldName
                    groupByFieldName:(NSString *)groupFieldName
                     extendedRequest:(nullable NSMutableDictionary<NSString *, NSString *> *)extendedRequest
                        successBlock:(nullable CYBCustomObjectsPageBlock)successBlock
                          errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Count of objects

/**
 Count of objects with extended Request
 
 @param className Name of class
 @param extendedRequest Extended set of request parameters
 @param successBlock Block with response instance and count of objects if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */

+ (CYBRequest *)countObjectsWithClassName:(NSString *)className
                          extendedRequest:(nullable NSMutableDictionary<NSString *, NSString *> *)extendedRequest
                             successBlock:(nullable CYBCountBlock)successBlock
                               errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Create Object

/**
 Create record
 
 @param object An instance of object that will be created
 @param successBlock Block with response instance and created object if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)createObject:(CYBCustomObject *)object
                successBlock:(nullable CYBCustomObjectBlock)successBlock
                  errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Multi Create

/**
 Create records
 
 @param objects An array of instances of objects that will be created
 @param className Name of class
 @param successBlock Block with response instance, NSArray of created objects if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)createObjects:(NSArray<CYBCustomObject *> *)objects
                    className:(NSString *)className
                 successBlock:(nullable CYBCustomObjectsBlock)successBlock
                   errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Update Object

/**
 Update record
 
 @param object An instance of object that will be updated
 @param successBlock Block with response instance and updated object if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)updateObject:(CYBCustomObject *)object
                successBlock:(nullable CYBCustomObjectBlock)successBlock
                  errorBlock:(nullable CYBErrorBlock)errorBlock;

/**
 Update record with Special update operators
 
 @param object An instance of object that will be updated
 @param specialUpdateOperators Special update operators
 @param successBlock Block with response instance and updated object if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)updateObject:(CYBCustomObject *)object
      specialUpdateOperators:(NSMutableDictionary<NSString *, NSString *> *)specialUpdateOperators
                successBlock:(nullable CYBCustomObjectBlock)successBlock
                  errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Multi Update

/**
 Update records
 
 @param objects An array of instances of objects that will be updated
 @param className Name of class
 @param successBlock Block with response instance, updated objects and not found objects Ids if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)updateObjects:(NSArray<CYBCustomObject *> *)objects
                    className:(NSString *)className
                 successBlock:(nullable void (^)(NSArray<CYBCustomObject *> *objects, NSArray<NSString *> *notFoundObjectsIds))successBlock
                   errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Delete Object

/**
 Delete object by identifier
 
 @param objectID ID of object to be removed.
 @param successBlock Block with response instance if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)deleteObjectWithID:(NSString *)objectID
                         className:(NSString *)className
                      successBlock:(nullable CYBSuccessBlock)successBlock
                        errorBlock:(nullable CYBErrorBlock)errorBlock;

/**
 Delete objects by IDs
 
 @param objectsIDs Array of IDs of objects to be removed.
 @param successBlock Block with response instance, NSArray of deleted objects Ids and NSArray of not found objects Ids if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)deleteObjectsWithIDs:(NSArray<NSString *> *)objectsIDs
                           className:(NSString *)className
                        successBlock:(nullable void (^)(NSArray<NSString *> *deletedObjectsIDs, NSArray<NSString *> *notFoundObjectsIDs, NSArray<NSString *> * wrongPermissionsObjectsIDs))successBlock
                          errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Permissions

/**
 Retrieve permissions for object with ID
 
 @param className Name of class
 @param ID Identifier of object which permissions will be retrieved
 @param successBlock Block with response instance and CYBCustomObjectPermissions instance if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)permissionsForObjectWithClassName:(NSString *)className
                                               ID:(NSString *)ID
                                     successBlock:(nullable void (^)(CYBCustomObjectPermissions *permissions))successBlock
                                       errorBlock:(nullable CYBErrorBlock)errorBlock;

//MARK: - Files

/**
 Upload file
 
 @param file File
 @param className Name of class
 @param objectID Identifier of object to which file will be uploaded
 @param fileFieldName Name of file field
 @param successBlock Block with response instance if the request is succeeded
 @param progressBlock Block with upload/download progress
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)uploadFile:(CYBCustomObjectFile *)file
                 className:(NSString *)className
                  objectID:(NSString *)objectID
             fileFieldName:(NSString *)fileFieldName
             progressBlock:(nullable CYBProgressBlock)progressBlock
              successBlock:(nullable void (^)(CYBCustomObjectFileUploadInfo *info))successBlock
                errorBlock:(nullable CYBErrorBlock)errorBlock;

/**
 Download file
 
 @param className Name of class
 @param objectID Identifier of object which file will be downloaded
 @param fileFieldName Name of file field
 @param successBlock Block with response instance and NSData instance if the request is succeeded
 @param progressBlock Block with upload/download progress
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)downloadFileFromClassName:(NSString *)className
                                 objectID:(NSString *)objectID
                            fileFieldName:(NSString *)fileFieldName
                            progressBlock:(nullable CYBProgressBlock)progressBlock
                             successBlock:(nullable void (^)(NSData *loadedData))successBlock
                               errorBlock:(nullable CYBErrorBlock)errorBlock;

/**
 Download file using background NSURLSession.
 
 @discussion If download is triggered by 'content-available' push - blocks will not be fired.
 
 @param className Name of class
 @param objectID Identifier of object which file will be downloaded
 @param fileFieldName Name of file field
 @param successBlock Block with response instance and NSData instance if the request is succeeded
 @param progressBlock Block with upload/download progress
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)backgroundDownloadFileFromClassName:(NSString *)className
                                           objectID:(NSString *)objectID
                                      fileFieldName:(NSString *)fileFieldName
                                      progressBlock:(nullable CYBProgressBlock)progressBlock
                                       successBlock:(nullable void (^)(NSData *loadedData))successBlock
                                         errorBlock:(nullable CYBErrorBlock)errorBlock;


/**
 Delete file
 
 @param className Name of class
 @param objectID Identifier of object form which file will be deleted
 @param fileFieldName Name of file field
 @param successBlock Block with response instance if the request is succeeded
 @param errorBlock Block with response instance if the request is failed.
 
 @return An instance of CYBRequest for cancel operation mainly.
 */
+ (CYBRequest *)deleteFileFromClassName:(NSString *)className
                               objectID:(NSString *)objectID
                          fileFieldName:(NSString *)fileFieldName
                           successBlock:(nullable CYBSuccessBlock)successBlock
                             errorBlock:(nullable CYBErrorBlock)errorBlock;

@end

NS_ASSUME_NONNULL_END
