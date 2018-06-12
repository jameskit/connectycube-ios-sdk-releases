//
//  CYBChat.h
//  ConnectyCube
//
//  Copyright © 2018 ConnectyCube. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ConnectyCube/CYBChatTypes.h>

@protocol CYBChatDelegate;

@class CYBUser;
@class CYBContactList;
@class CYBChatMessage;
@class CYBPrivacyList;

NS_ASSUME_NONNULL_BEGIN

/**
 CYBChat class interface.
 This class is the main entry point to work with ConnectyCube Chat API.
 */
NS_SWIFT_NAME(Chat)
@interface CYBChat : NSObject

/**
 Get CYBChat singleton.
 
 @return CYBChat Chat service singleton.
 */
@property (nonatomic, readonly, class) CYBChat *instance;

/**
 Determines whether chat is connected. Returns YES if the connection is open, and the stream has
 been properly established.
 
 @discussion If the stream is neither disconnected, nor connected, then a connection is currently
 being established. If this method returns YES, then it is ready for you to start sending and
 receiving elements.
 */
@property (assign, nonatomic, readonly) BOOL isConnected;

/** Returns YES is the connection is currently connecting. */
@property (assign, nonatomic, readonly) BOOL isConnecting;

/** Returns contact list. */
@property (nonatomic, readonly, nullable) CYBContactList *contactList;

/** Returns current chat user. */
@property (nonatomic, readonly, copy, nullable) CYBUser *currentUser;

/** Return current resource. */
@property (nonatomic, readonly, copy, nullable) NSString *currentResource;

/**Unavailable initializer.*/
- (id)init NS_UNAVAILABLE;

/**Unavailable initializer.*/
+ (instancetype)new NS_UNAVAILABLE;

//MARK: - Multicast Delegate

/**
 Adds the given delegate implementation to the list of observers.
 
 @param delegate The delegate to add.
 */
- (void)addDelegate:(id<CYBChatDelegate>)delegate;

/**
 Removes the given delegate implementation from the list of observers.
 
 @param delegate The delegate to remove.
 */
- (void)removeDelegate:(id<CYBChatDelegate>)delegate;

/** Removes all delegates. */
- (void)removeAllDelegates;

/** Returns array of all delegates. */
- (NSArray<id <CYBChatDelegate>> *)delegates;

@end

/**
 Methods provided connections to chat
 */
//MARK: - Connection
@interface CYBChat(Connection)

/**
 Connect to ConnectyCube Chat with completion.
 
 @param userID User's ID.
 @param password User's password.
 @param completion Completion block with failure error.
 */
- (void)connectWithUserID:(NSUInteger)userID
                 password:(NSString *)password
               completion:(nullable CYBChatErrorBlock)completion;
/**
 Connect to ConnectyCube Chat with completion.
 
 @param userID User's ID.
 @param password User's password.
 @param completion Completion block with failure error.
 */
- (void)connectWithUserID:(NSUInteger)userID
                 password:(NSString *)password
                 resource:(NSString *)resource
               completion:(nullable CYBChatErrorBlock)completion;

/**
 Disconnect current user from Chat and leave all rooms.
 
 @param completion  Completion block with failure error.
 */
- (void)disconnectWithCompletionBlock:(nullable CYBChatErrorBlock)completion;

/**
 Run force reconnect. This method disconnects from chat and runs reconnection logic. Works only if
 autoReconnectEnabled=YES. Otherwise it does nothing.
 */
- (void)forceReconnect;

@end

//MARK: User status

@interface CYBChat(UserStatus)

/**
 Send presence message with status.
 
 @param status Presence status.
 
 @return YES if the request was sent successfully. Otherwise - see log.
 */
- (BOOL)sendPresenceWithStatus:(NSString *)status;

@end

@interface CYBChat(MessagesStatus)

/**
 Send "read" status for message and update "read" status on a server.
 
 @param message CYBChatMessage message to mark as read.
 @param completion Completion block with failure error.
 */
- (void)readMessage:(CYBChatMessage *)message completion:(nullable CYBChatErrorBlock)completion;

/**
 Send "delivered" status for message.
 
 @param message CYBChatMessage message to mark as delivered.
 @param completion Completion block with failure error.
 */
- (void)markAsDelivered:(CYBChatMessage *)message completion:(nullable CYBChatErrorBlock)completion;

@end

//MARK: - Privacy

@interface CYBChat(Privacy)

/**
 Retrieve a privacy list by name.
 CYBChatDelegate's method 'didReceivePrivacyList:' will be called if success or
 'didNotReceivePrivacyListWithName:error:' if there is an error
 
 @param privacyListName name of privacy list
 */
- (void)retrievePrivacyListWithName:(NSString *)privacyListName;

/**
 Retrieve privacy list names.
 CYBChatDelegate's method 'didReceivePrivacyListNames:' will be called if success or
 'didNotReceivePrivacyListNamesDueToError:' if there is an error
 */
- (void)retrievePrivacyListNames;

/**
 Create/edit a privacy list.
 CYBChatDelegate's method 'didReceivePrivacyList:' will be called
 
 @param privacyList instance of CYBPrivacyList
 */
- (void)setPrivacyList:(nullable CYBPrivacyList *)privacyList;

/**
 Set a default privacy list.
 CYBChatDelegate's method 'didSetDefaultPrivacyListWithName:' will be called if success or
 'didNotSetDefaultPrivacyListWithName:error:' if there is an error
 
 @param privacyListName name of privacy list
 */
- (void)setDefaultPrivacyListWithName:(nullable NSString *)privacyListName;

/**
 Remove a privacy list.
 
 CYBChatDelegate's method 'didRemovedPrivacyListWithName:' will be called if success or
 'didNotSetPrivacyListWithName:error:' if there is an error
 
 @param privacyListName name of privacy list
 */
- (void)removePrivacyListWithName:(NSString *)privacyListName;

@end

//MARK: - System Messages

@interface CYBChat(SystemMessage)

/**
 Send system message to dialog.
 
 @param message CYBChatMessage instance of message to send.
 @param completion Completion block with failure error.
 */
- (void)sendSystemMessage:(CYBChatMessage *)message
               completion:(nullable CYBChatErrorBlock)completion;
@end

//MARK: - Last Activity

@interface CYBChat(LastActivity)

/**
 Get Last activity for user with id.
 
 @param userID User ID.
 @param completion completion block with last activity in seconds and error.
 */
- (void)lastActivityForUserWithID:(NSUInteger)userID
                       completion:(CYBLastActivityBlock)completion;

/**
 Get Last activity for user with id.
 
 @param userID User ID
 @param timeout timeout
 @param completion Completion block with last activity in seconds and error.
 */
- (void)lastActivityForUserWithID:(NSUInteger)userID
                          timeout:(NSTimeInterval)timeout
                       completion:(CYBLastActivityBlock)completion;
@end

//MARK: - Send pings to the server or a userID

@interface CYBChat(Ping)

/**
 Send ping to server.
 
 @param completion Completion block with ping time interval and success flag.
 */
- (void)pingServer:(CYBPingCompleitonBlock)completion;

/**
 Send ping to server with timeout.
 
 @param timeout Ping timeout.
 @param completion Completion block with ping time interval and success flag.
 */
- (void)pingServerWithTimeout:(NSTimeInterval)timeout completion:(CYBPingCompleitonBlock)completion;

/**
 Send ping to user.
 @note You must be subscribed to user in contact list in order to successfully ping him.
 
 @param userID User ID.
 @param completion Completion block with ping time interval and success flag.
 */
- (void)pingUserWithID:(NSUInteger )userID completion:(CYBPingCompleitonBlock)completion;

/**
 Send ping to user with timeout.
 @note You must be subscribed to user in contact list in order to successfully ping him.
 
 @param userID User ID.
 @param timeout Timeout in seconds.
 @param completion Completion block with ping time interval and success flag.
 */
- (void)pingUserWithID:(NSUInteger)userID timeout:(NSTimeInterval)timeout completion:(CYBPingCompleitonBlock)completion;

@end

//MARK: - Contact list

@interface CYBChat(ContactList)
/**
 After establishing a session, a client SHOULD send initial presence to the server in order to signal
 its availability for communications.
 */
@property (assign, nonatomic) BOOL manualInitialPresence;

/**
 Add user to contact list request
 
 @param userID  ID of user which you would like to add to contact list
 @param completion The block which informs whether a request was delivered to server or not. If the request is succeeded error is nil.
 */
- (void)addUserToContactListRequest:(NSUInteger)userID completion:(nullable CYBChatErrorBlock)completion;

/**
 Remove user from contact list.
 
 @param userID ID of user which you would like to remove from contact list
 @param completion The block which informs whether a request was delivered to server or not. If the request is succeeded error is nil.
 */
- (void)removeUserFromContactList:(NSUInteger)userID completion:(nullable CYBChatErrorBlock)completion;

/**
 Confirm add to contact list request.
 
 @param userID ID of user from which you would like to confirm add to contact request.
 @param completion The block which informs whether a request was delivered to server or not. If the request is succeeded error is nil.
 */
- (void)confirmAddContactRequest:(NSUInteger)userID completion:(nullable CYBChatErrorBlock)completion;

/**
 Reject add to contact list request or cancel previously-granted subscription request.
 
 @param userID ID of user from which you would like to reject add to contact request.
 @param completion The block which informs whether a request was delivered to server or not. If therequest is succeeded error is nil.
 */
- (void)rejectAddContactRequest:(NSUInteger)userID completion:(nullable CYBChatErrorBlock)completion;

@end

NS_ASSUME_NONNULL_END
