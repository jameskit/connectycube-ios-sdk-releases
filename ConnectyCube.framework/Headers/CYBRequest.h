//
//  CYBRequest.h
//  ConnectyCube
//
//  Copyright © 2018 ConnectyCube. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CYBRequest;

NS_ASSUME_NONNULL_BEGIN

/** Blocks typedef */
typedef void(^CYBProgressBlock)(float progress);
typedef void(^CYBErrorBlock)(NSError *error);
typedef void(^CYBSuccessBlock)(void);

/**
 *  CYBRequest class interface.
 *  This class represents all requests to ConnectyCube API.
 */
NS_SWIFT_NAME(Request)
@interface CYBRequest : NSObject

/// The NSURLSessionTask class is the base class for tasks in a URL session.
@property (nonatomic, readonly) NSURLSessionTask *task;

/// Determines if NSURLSessionTask was canceled.
@property (nonatomic, getter=isCancelled, readonly) BOOL canceled;

/** Unavailable Constructors */
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 *  Cancels NSURLSessionTask associated with request.
 */
- (void)cancel;

+ (void)cancelAllRequests:(dispatch_block_t)completion;

@end

NS_ASSUME_NONNULL_END
