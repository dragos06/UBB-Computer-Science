USE MiniFacebook

BEGIN TRANSACTION
	UPDATE Posts SET post_shares = post_shares + 50 WHERE user_id=1;
	COMMIT;