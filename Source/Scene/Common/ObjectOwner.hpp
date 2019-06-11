namespace Soon
{
	struct ObjectOwner : public Component
	{
		public:
			ObjectOwner( Entity& entity, Object* obj )
			{
				_owner = obj;
			}
			~ObjectOwner( void )
			{

			}

			Object* _owner;
	};
}
